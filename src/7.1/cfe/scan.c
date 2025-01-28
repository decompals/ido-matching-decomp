#include "common.h"

char* ident = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/scan.c,v 1.32 1995/02/27 22:12:08 rdahl Exp $";

#define BUFFER_SIZE 0x8000
#define input() (isprint(*inbuf_ptr) ? *inbuf_ptr++ : input_any_char())
#define unput() inbuf_ptr--; if (*inbuf_ptr == '\n') { yyline--; }

typedef struct TokenIdentifier {
    int unk_00;
    Symbol* unk_04;
    int unk_08;
} TokenIdentifier;

union YYLVAL {
    UnkOmega* node;
    TokenIdentifier identifier;
    int loc;
};

/* .bss       */
/* 0x10023A90 */ static char input_buffer[BUFFER_SIZE + 1];
/* 0x1002BA94 */ static char* inbuf_ptr;
/* 0x1002BA98 */ static int offset_in_file;
/* 0x1002BA9C */ static unsigned int tokenbuf_size;
/* 0x1002BAA0 */ static void* tokenbuf_base;
/* 0x1002BAA4 */ static char* token;
/* 0x1002BAA8 */ static int* wstring_base;
/* 0x1002BAAC */ static int input_file_status;
/* 0x1002BAB0 */ static FILE* input_file; // temp file used for buffering
/* 0x1002BAB4 */ static int input_file_eof;

static char input_any_char(void);
static char next_char(void);
ParseSymbol* mk_parse_symb(Symbol* symb, int id, int arg2);

void adjust_vwbuf(void) {
    tokenbuf_size *= 1.333;
    tokenbuf_base = Realloc(tokenbuf_base, tokenbuf_size);
    token = tokenbuf_base;
    wstring_base = tokenbuf_base;
}

Location* yylocation(Location* arg0) {
    Location ret;
    
    ret.offset = (int)(inbuf_ptr - input_buffer) + offset_in_file;
    ret.file = yyfile;
    ret.line = yyline;

    *arg0 = ret;
    return arg0;
}

char* get_buffer(int size) {
    if (size != BUFFER_SIZE) {
        return NULL;
    }
    input_file_status = 0;
    return &input_buffer[1];
}

void cpp_write(char* data, int size) {
    if (size != BUFFER_SIZE && input_file_status == 0) {
        input_file_status = 1;
        input_buffer[size + 1] = 0;
    } else if (size == BUFFER_SIZE && input_file_status == 0) {
        char* name = tempnam("", "");

        input_file = fopen(name, "w+");
        if (input_file == NULL) {
            error(0x2001A, LEVEL_FATAL, -1, infile != NULL ? infile : "");
        } else {
            // remove this file when it's closed
            unlink(name);
        }

        fwrite(data, 1, size, input_file);
        if (ferror(input_file)) {
            error(0x10047, LEVEL_FATAL, -1, name);
        }
        input_file_status = 2;
    } else {
        fwrite(data, 1, size, input_file);
        if (ferror(input_file)) {
            error(0x10047, LEVEL_FATAL, -1, "temporary for buffering");
        }
    }
}

void free_buffer(char* arg0) {

}

static int unescape(char c) {
    switch (c) {
        case 'a':
            return '\a';
        case 'b':
            return '\b';
        case 'f':
            return '\f';
        case 'n':
            return '\n';
        case 'r':
            return '\r';
        case 't':
            return '\t';
        case 'v':
            return '\v';
    }
}

static int scan_line_directive(int* line, char* filename, int* hasFilename) {
    char c;
    char* ptr;

    while (c = input()) {
        // skip whitespaces
        if (c == ' ' || c == '\t') {
            continue;
        }
        
        if (c == '\n' || c == 0) {
            return 0;
        }
        // digit encountered -> read line number
        if (isdigit(c)) {
            break;
        }

        if (c == 'l' && (c = input()) == 'i' && (c = input()) == 'n' && (c = input()) == 'e') {
            // "line" word
            continue;
        } else {
out:
            if (origfile == 0) {
                register_file("", 1);
            }
        
            if (c != '\n') {
                while (c = input()) {
                    if (c == '\n') {
                        break;
                    }
                }
            }
        
            return FALSE;
        }
    }

    // read line number
    *line = c - '0';
    while (c = (next_char() == '\n' ? '\n' : input())) {
        if (isdigit(c)) {
            *line = *line * 10 + c - '0';
        } else {
            if (c != '\n') {
                unput();
            }
            break;
        }
    }

    while (c = (next_char() == '\n' ? '\n' : input())) {
        if (c != ' ' && isprint(c)) {
            break;
        }
        if (c == '\n') {
            // only line, without filename
            *hasFilename = FALSE;
            return TRUE;
        }
    }

    // filename starts with quote
    if (c != '"') {
        goto out;
    }

    // copy filename
    ptr = filename;
    while ((c = input()) != '"') {
        if (c == '\n' || c == 0) {
            goto out;
        }
        *ptr++ = c;
    }
    *ptr = 0;

    *hasFilename = TRUE;
    return TRUE;
}

static int fill_input_buffer(void) {
    int nread;
    int unused[3];
    int line;
    char c;
    int hasFilename;

    if (inbuf_ptr == NULL) {
        if (input_file_status == 2) {
            rewind(input_file);
        }
        offset_in_file = 0;
    } else if (*inbuf_ptr == 0) {
        if (input_file_status == 2 && input_file_eof) {
            return FALSE;
        }

        if (input_file_status == 1) {
            return FALSE;
        }

        if (input_file_status == 0) {
            error(0x20095, LEVEL_WARNING, 0);
            return FALSE;
        }

        // copy one char to the new buffer
        inbuf_ptr--;
        input_buffer[0] = *inbuf_ptr;

        offset_in_file += (int)(inbuf_ptr - input_buffer);
        inbuf_ptr = input_buffer + 1;
    }

    if (input_file_status == 2) {        
        if (fseek(input_file, offset_in_file, SEEK_SET) == -1) {
            return 0;
        }

        nread = fread(input_buffer + 1, 1, BUFFER_SIZE, input_file);
        input_buffer[1 + nread] = 0;
        if (ferror(input_file)) {
            error(0x10046, LEVEL_FATAL, -1, "temporary for buffering");
            return 0;
        }
        if (nread == 0) {
            return 0;
        }

        if (feof(input_file)) {
            input_file_eof = TRUE;
        } else {
            input_file_eof = FALSE;
        }
    }

    if (inbuf_ptr == NULL) {
        inbuf_ptr = input_buffer + 1;
        if (input_buffer[1] == '#') {
            inbuf_ptr++;
            if (scan_line_directive(&line, token, &hasFilename) == 1) {
                if (hasFilename) {
                    register_file(token, line);
                } else {
                    register_file("", 1);
                }

                if (hasFilename) {                    
                    while (c = input()) {
                        if (c == '\n') {
                            break;
                        }
                    }
                }
                unput();
            }
        } else {
            register_file(infile != NULL ? infile : "", 1);
        }
    }

    return TRUE;
}

static void nullsub(void) {

}

static char next_char(void) {
    if (inbuf_ptr == NULL || *inbuf_ptr == 0) {
        fill_input_buffer();
    }
    return *inbuf_ptr;
}

static char input_any_char(void) {
    CppLineArr* temp;
    
    if (inbuf_ptr == NULL || *inbuf_ptr == 0) {
        if (fill_input_buffer()) {
            return input();
        }

        return *inbuf_ptr++;
    }
    
    if (*inbuf_ptr == '\n') {
        yyline++;
        if (cppline == 0 || ((int)(inbuf_ptr - input_buffer) + offset_in_file) != cpplinearr.loc[cppline].offset) {
            char* ptr = inbuf_ptr + 1;
            if (*ptr != '#') {
                while (*ptr == ' ' || *ptr == '\t') {
                    ptr++;
                }

                if (*ptr != '\n') {
                    cppline++;
                    if (cppline >= (unsigned int)cpplinearr.size) {
                        cpplinearr.size = cppline + 0x100;
                        cpplinearr.loc = Realloc(cpplinearr.loc, cpplinearr.size * (signed)sizeof(Location));
                        temp = &cpplinearr;
                        yylocation(&temp->loc[cppline]);
                    } else {
                        temp = &cpplinearr;
                        yylocation(&temp->loc[cppline]);
                    }
                }
            }
        }
        inbuf_ptr++;
        return '\n';
    }

    if (*inbuf_ptr == '\t' || *inbuf_ptr == '\f' || *inbuf_ptr == '\v') {
        return *inbuf_ptr++;
    }

    return *inbuf_ptr++;
}

static float scan_float(char* start, char* end, int arg2) {
    if (start < end) {
        if (end[-1] != 0) {
            *end = 0;
        }
        return str_to_float(start, arg2, 1);
    }
}

static double scan_double(char* start, char* end, int arg2) {
    if (start < end) {
        if (end[-1] != 0) {
            *end = 0;
        }
        return str_to_double(start, arg2, 1);
    }
}

static int scan_number(int hasDot) {
    int isHex = FALSE;
    int isOctal = FALSE;
    char* buf_ptr;
    int hasUnsignedSuffix = FALSE;
    int hasLongSuffix = FALSE;
    int hasLongLongSuffix = FALSE;
    int hasFloatSuffix = FALSE;
    int isFloat = FALSE;
    int isEmptyHex = FALSE;    
    char* int_ptr;
    char c;
    char invalidOctalDigit = 0;        
    char c1;

    if (hasDot) {
        isFloat = TRUE;
        *token = '.';
        buf_ptr = token + 1;
    } else {
        buf_ptr = token;
    }

    if(isFloat) {} // required to match

    while (c = input()) {
        if (isdigit(c)) {
            *buf_ptr++ = c;

            if (buf_ptr == token + 1 && c == '0') {
                isOctal = TRUE;
            }
            if (isOctal && c > '7' && invalidOctalDigit == 0) {
                invalidOctalDigit = c;
            }
        } else if (c == 'X' || c == 'x') {
            if (buf_ptr == token + 1 && *token == '0') {
                isHex = TRUE;
                *buf_ptr++ = c;
                while (c = input()) {
                    if (!isxdigit(c)) {
                        goto out;
                    }
                    *buf_ptr++ = c;
                }
                // continue
            } else {
                break;
            }
        } else if (c == '.') {
            if (hasDot) {
                break;
            }

            isOctal = FALSE;
            hasDot = TRUE;
            isFloat = TRUE;
            *buf_ptr++ = c;
        } else if (c == 'e' || c == 'E') {
            *buf_ptr++ = c;
            isOctal = FALSE;
            isFloat = TRUE;

            c1 = input();
            if (c1 == '+' || c1 == '-') {
                *buf_ptr++ = c1;
                c1 = input();
            }

            if (isdigit(c1)) {
                while (isdigit(c1)) {
                    *buf_ptr++ = c1;
                    c1 = input();
                }
            } else {
                error(0x2000E, LEVEL_ERROR, curloc, c1);
            }
            break;
        } else {
            break;
        }
    }
out:
    unput();

    while (c = input()) {
        if (isFloat && (c == 'f' || c == 'F')) {
            hasFloatSuffix = TRUE;
            *buf_ptr++ = c;
            break;
        } else if (!isFloat && !hasUnsignedSuffix && (c == 'u' || c == 'U')) {
            hasUnsignedSuffix = TRUE;
            *buf_ptr++ = c;
            if (hasLongLongSuffix) {
                break;
            }
        } else if (!isFloat && !hasLongLongSuffix && (c == 'l' || c == 'L')) {
            if (hasLongSuffix) {
                hasLongLongSuffix = TRUE;
                hasLongSuffix = FALSE;
            } else {
                hasLongSuffix = TRUE;
            }
            *buf_ptr++ = c;
        } else if (isFloat && (c == 'l' || c == 'L')) {
            hasLongSuffix = TRUE;
            *buf_ptr++ = c;
            break;
        } else {
            unput();
            break;
        }
    }

    if (isFloat) {
        if (hasFloatSuffix) {
            scan_float(token, buf_ptr, curloc);
            yylval.node = make(0x65, curloc, float_type, string_to_symbol(token, buf_ptr - token));
        } else {
            scan_double(token, buf_ptr, curloc);
            yylval.node = make(0x65, curloc, double_type, string_to_symbol(token, buf_ptr - token));
        }
        return CONSTANT;
    } else {
        unsigned long longValue = 0;
        int unused;
        unsigned long long longLongValue = 0;
        int isLongLong = hasLongLongSuffix;
        unsigned int bitSize = 0;
        int hasTypePromotion = 0;
        int hasOverflow = FALSE;

        if (isLongLong && IS_STRICT_ANSI) {
            error(0x20131, LEVEL_WARNING, curloc, "long long constants (LL)");
        }

        if (isHex) {
            if (buf_ptr == token + 2) {
                isEmptyHex = TRUE;
                error(0x2010B, LEVEL_DEFAULT, curloc);
            }
            for (int_ptr = token + 2; int_ptr < buf_ptr; int_ptr++) {
                if (!isxdigit(*int_ptr)) {
                    break;
                }

                bitSize += 4;
                if (!isEmptyHex && !hasOverflow && (isLongLong && longLongValue > __ULONGLONG_MAX / 16 || longValue > ULONG_MAX / 16)) {
                    if (isLongLong || IS_STRICT_ANSI) {
                        hasOverflow = TRUE;
                    } else {
                        hasTypePromotion = TRUE;
                        isLongLong = TRUE;
                        longLongValue = longValue;                        
                        longValue = 0;
                    }
                }

                if (isLongLong) {
                    longLongValue = (longLongValue << 4) + (isdigit(*int_ptr) ? *int_ptr - '0' : islower(*int_ptr) ? *int_ptr - 'a' + 10 : *int_ptr - 'A' + 10);
                } else {
                    longValue = (longValue << 4) + (isdigit(*int_ptr) ? *int_ptr - '0' : islower(*int_ptr) ? *int_ptr - 'a' + 10 : *int_ptr - 'A' + 10);
                }
            }
        } else if (isOctal && invalidOctalDigit == 0) {
            for (int_ptr = token + 1; int_ptr < buf_ptr; int_ptr++) {
                if (*int_ptr < '0' || *int_ptr > '7') {
                    break;
                }
                bitSize += 3;
                if (!hasOverflow && (isLongLong && longLongValue > __ULONGLONG_MAX / 8 || longValue > ULONG_MAX / 8)) {
                    if (isLongLong || IS_STRICT_ANSI) {
                        hasOverflow = TRUE;
                    } else {
                        hasTypePromotion = TRUE;
                        isLongLong = TRUE;
                        longLongValue = longValue;                        
                        longValue = 0;
                    }
                }

                if (isLongLong) {
                    longLongValue = (longLongValue << 3) + *int_ptr - '0';
                } else {
                    longValue = (longValue << 3) + *int_ptr - '0';
                }
            }
        } else {
            if (invalidOctalDigit) {
                error(0x20019, LEVEL_ERROR, curloc, invalidOctalDigit);
                isOctal = FALSE;
            }

            for (int_ptr = token; int_ptr < buf_ptr; int_ptr++) {
                unsigned int digit;
                if (!isdigit(*int_ptr)) {
                    break;
                }
                digit = *int_ptr - '0';
                if (!hasOverflow && (isLongLong && (longLongValue > __ULONGLONG_MAX / 10 || longLongValue * 10 > __ULONGLONG_MAX - digit) || (longValue > 0xFFFFFFFF / 10 || longValue * 10 > 0xFFFFFFFF - digit))) {
                    if (isLongLong || IS_STRICT_ANSI) {
                        hasOverflow = TRUE;
                    } else {
                        hasTypePromotion = TRUE;
                        isLongLong = TRUE;
                        longLongValue = longValue;                        
                        longValue = 0;
                    }
                }

                if (isLongLong) {
                    longLongValue = longLongValue * 10 + digit;
                } else {
                    longValue = longValue * 10 + digit;
                }
            }
        }

        if (!isEmptyHex) {
            if (hasOverflow) {
                error(0x2000F, LEVEL_DEFAULT, curloc);
            } else if ((IS_STRICT_ANSI || options[OPTION_FULLWARN]) && hasTypePromotion){
                error(0x20010, LEVEL_DEFAULT, curloc);
            }
        }

        if (hasUnsignedSuffix && isLongLong) {
            yylval.node = make_uiconstant(curloc, ulonglong_type, (unsigned long long)longLongValue);
        } else if (hasUnsignedSuffix && hasLongSuffix) {
            yylval.node = make_uiconstant(curloc, ulong_type, (unsigned long)longValue);
        } else if (hasUnsignedSuffix) {
            yylval.node = make_uiconstant(curloc, uint_type, (unsigned int)longValue);
        } else if (isLongLong) {
            if (longLongValue <= (unsigned long long)__LONGLONG_MAX) {
                yylval.node = make_iconstant(curloc, longlong_type, (long long)longLongValue);
            } else {
                yylval.node = make_uiconstant(curloc, ulonglong_type, (unsigned long long)longLongValue);
            }
        } else if (hasLongSuffix) {
            if (longValue <= LONG_MAX || !options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1)) {
                yylval.node = make_iconstant(curloc, long_type, (long)longValue);
            } else {
                yylval.node = make_uiconstant(curloc, ulong_type, (unsigned long)longValue);
            }
        } else if (isHex || isOctal) {
            if (IS_ANSI) {
                if (longValue <= LONG_MAX) {
                    yylval.node = make_iconstant(curloc, int_type, (int)longValue);
                } else {
                    yylval.node = make_uiconstant(curloc, uint_type, (unsigned int)longValue);
                }
            } else {
                if (longValue <= LONG_MAX) {
                    yylval.node = make_iconstant(curloc, int_type, (int)longValue);
                } else {
                    yylval.node = make_iconstant(curloc, long_type, (long)longValue);
                }
            }
        } else if (longValue <= LONG_MAX) {
            yylval.node = make_iconstant(curloc, int_type, (int)longValue);
        } else if (longValue <= LONG_MAX || !options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1)) {
            yylval.node = make_iconstant(curloc, long_type, (long)longValue);
        } else {
            yylval.node = make_uiconstant(curloc, ulong_type, (unsigned long)longValue);
        }

        if (!options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1) && long_type->unk_18 == int_type->unk_18) {
            if (yylval.node->unk_08 == long_type) {
                yylval.node->unk_08 = int_type;
            } else if (yylval.node->unk_08 == ulong_type) {
                yylval.node->unk_08 = uint_type;
            }
        }

        // required to match
        if (1) { }
        if (1) { }
        if (1) { }
        if (1) { }
        
        if (options[OPTION_LINT_FLAGS] && !(options[OPTION_LINT_FLAGS] & 0x40) && (isHex || isOctal && bitSize != 0) && bitSize < sizeof_type(yylval.node->unk_08->unk_04)) {
            error(0x7014D, LEVEL_WARNING, curloc, bitSize, isHex ? "hex" : "octal", get_type_name(yylval.node->unk_08->unk_04));
        }
        return CONSTANT;
    }
}

const char unreferenced_string_1[] = "sizeof(wchar_t) <= sizeof(uint_t)";
const char unreferenced_string_2[] = "scan.c";

static int read_string_character(char stopChar, char* out_buf, int forbidNumeric, int* hasNumeric) {
    int i;
    
restart:
    *out_buf = input();
    switch (*out_buf) {
        unsigned int value;
        char c;

        case 0:
            goto eof;
        case '\n':
            error(0x20014, LEVEL_ERROR, curloc);
return_false:
            return FALSE;
        case '\\':    
            switch(*out_buf = input()) {
                case '\n':
                    goto restart;
                case 'b':
                case 'f':
                case 'n':
                case 'r':
                case 't':
                case 'v':
                    *out_buf = unescape(*out_buf);
                    break;
                case 'a':
                    if (IS_ANSI) {
                        *out_buf = unescape(*out_buf);
                    } else {
                        *out_buf = 'a';
                        error(0x20018, LEVEL_DEFAULT, curloc, *out_buf);
                    }
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    if (!forbidNumeric) {        
                        value = *out_buf - '0';
                        for (i = 0; i < 2; i++) {
                            c = input();
                            if (c >= '0' && c <= '7') {
                                value = value * 8 + c - '0';
                            } else {
                                unput();
                                break;
                            }
                        }
        
                        if (value > 255) {
                            error(0x20015, LEVEL_DEFAULT, curloc, value, 255);
                        }
                        *out_buf = value;
                        break;
                    }
                    *hasNumeric = TRUE;
                    break;
                case 'x':
                    if (IS_ANSI && !forbidNumeric) {
                        c = input();
                        if (isxdigit(c)) {        
                            value = isdigit(c) ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 10;                        
                            c = input();
                            while (isxdigit(c)) {
                                value = value * 16 + (isdigit(c) ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 10);
                                c = input();
                            }
                            unput();
                            if (value > 255 || (int)value < 0) {
                                error(0x20016, LEVEL_DEFAULT, curloc, value, 255);
                            }
                            *out_buf = value;
                            break;
                        } else {
                            unput();
                        }
                    }
        
                    *out_buf = 'x';
                    if (!IS_ANSI) {
                        error(0x20018, LEVEL_DEFAULT, curloc, *out_buf);
                    }
                    if (forbidNumeric) {
                        *hasNumeric = TRUE;
                    }
                    break;
                case 0:
eof:
                    error(0x20017, LEVEL_ERROR, curloc);
                    goto return_false;
                default:                    
                    if (islower(*out_buf)) {
                        error(0x20018, LEVEL_DEFAULT, curloc, *out_buf);
                    }
                    break;
            }
            break;
        default:
            if (*out_buf == stopChar) {
                goto return_false;
            }
            break;
    }
    
    return TRUE;
}

static int read_wstring_character(char stopChar, char* buffer) {
    char c;
    int i;
    unsigned int value;    
    int unused;
    int hasOverflow = FALSE;
    int nearlyOverflow = FALSE;
    int hasNumeric = FALSE;    

    if (!read_string_character(stopChar, buffer, TRUE, &hasNumeric)) {
        return FALSE;
    }

    if (1) {} if (1) {} if (1) {} if (1) {}

    if (hasNumeric) {
        // large numeric values are allowed in wide strings
        switch(*buffer) {
            case 'x':
                if (IS_ANSI) {
                    c = input();
                    if (isxdigit(c)) {        
                        value = isdigit(c) ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 10;                        
                        c = input();
                        while (isxdigit(c)) {
                            value = value * 16 + (isdigit(c) ? c - '0' : islower(c) ? c - 'a' + 10 : c - 'A' + 10);
                            if (nearlyOverflow) {
                                hasOverflow = TRUE;
                                break;
                            }
                            if (value >> 28) {
                                nearlyOverflow = TRUE;
                            }
                            c = input();
                        }
                        unput();
                        if (hasOverflow) {
                            error(0x20016, LEVEL_DEFAULT, curloc, value, ULONG_MAX);
                        }
                        *(int*)buffer = value;
                        break;
                    } else {
                        unput();
                    }
                }
                *(int*)buffer = *buffer;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                value = *buffer - '0';
                for (i = 0; i < 2; i++) {
                    c = input();
                    if (c >= '0' && c <= '7') {
                        value = value * 8 + c - '0';
                    } else {
                        unput();
                        break;
                    }
                }
                *(int*)buffer = value;
                break;
        }
    } else {
        *(int*)buffer = *buffer;
    }

    return TRUE;
}

static int scan_string(void) {
    char* ptr;    
    unsigned int len;
    int unused;
    int hasNumeric = FALSE;

    for (ptr = token, len = 0; read_string_character('"', ptr, FALSE, &hasNumeric); ptr++, len++) {
        if (len >= tokenbuf_size - 1) {
            adjust_vwbuf();
            ptr = &token[len];
        }
    }

    *ptr = 0;
    yylval.node = make(0x65, curloc, array_type, token, ptr - token + 1);
    return STRING;
}

static int scan_wstring(void) {
    int* ptr;
    unsigned int len;

    for (ptr = wstring_base, len = 0; read_wstring_character('"', (char*)ptr); ptr++, len++) {
        if (len >= (tokenbuf_size >> 2) - 1) {
            adjust_vwbuf();
            ptr = &wstring_base[len];
        }
    }

    *ptr = 0;
    yylval.node = make(0x68, curloc, array_type, wstring_base, len + 1);
    return WSTRING;
}

static int scan_char(void) {
    char* ptr;
    int sp30 = 0;
    unsigned int len;

    for (ptr = token; read_string_character('\'', ptr, 0, &sp30); ptr++) {
    }

    len = ptr - token;
    if (len > 4 || len == 0) {
        error(0x20011, LEVEL_DEFAULT, curloc);
    }
    len = ptr - token;
    switch(len) {
        case 0:
            yylval.node = make_iconstant(curloc, int_type, 0);
            break;
        case 1:
            yylval.node = make_iconstant(curloc, int_type, options[OPTION_SIGNED] ? (signed char)token[0] : (unsigned char)token[0]);
            break;
        case 2:
            if (options[OPTION_ENDIANNESS]) {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[OPTION_SIGNED] ? (signed char)token[0] : (unsigned char)token[0]) << 8) + token[1]));
            } else {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[OPTION_SIGNED] ? (signed char)token[1] : (unsigned char)token[1]) << 8) + token[0]));
            }
            break;
        case 3:
            if (options[OPTION_ENDIANNESS]) {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[OPTION_SIGNED] ? (signed char)token[0] : (unsigned char)token[0]) << 16) + (token[1] << 8) + token[2]));
            } else {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[OPTION_SIGNED] ? (signed char)token[2] : (unsigned char)token[2]) << 16) + (token[1] << 8) + token[0]));
            }
            break;
        default:
            if (options[OPTION_ENDIANNESS]) {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[OPTION_SIGNED] ? (signed char)token[0] : (unsigned char)token[0]) << 24) + (token[1] << 16) + (token[2] << 8) + token[3]));
            } else {
                yylval.node = make_iconstant(curloc, int_type, (unsigned int)(((options[OPTION_SIGNED] ? (signed char)token[3] : (unsigned char)token[3]) << 24) + (token[2] << 16) + (token[1] << 8) + token[0]));
            }
            break;
    }

    return CONSTANT;
}

static int scan_wchar(void) {
    int* ptr;

    for (ptr = wstring_base; read_wstring_character('\'', (char*)ptr); ptr++) {
    }

    yylval.node = make_iconstant(curloc, long_type, *wstring_base);
    return CONSTANT;
}

void func_004141BC(void) {

}

static int scan_identifier(char firstChar) {
    char c;
    char* ptr = token;
    int len;
    int tp;

    *ptr++ = firstChar;

    while (c = input()) {
        if (!(isalnum(c) || c == '_' || c == '$' && options[OPTION_DOLLAR])) {
            unput();
            break;
        }

        if ((unsigned int)(ptr - token) >= tokenbuf_size) {
            len = ptr - token;
            adjust_vwbuf();
            ptr = &token[len];
        }
        *ptr++ = c;
    }

    yylval.identifier.unk_04 = string_to_symbol(token, ptr - token);
    yylval.identifier.unk_08 = curloc;
    yylval.identifier.unk_00 = 0;

    if (yylval.identifier.unk_04->unk_04 != NULL) {
        tp = yylval.identifier.unk_04->unk_04->unk_04; 
        if (tp == -1) {
            if (cur_lvl->unk_04) {
                return TYPE_IDENT;
            } 
            yylval.identifier.unk_00 = 1;
            return IDENTIFIER;
        }
    
        if (tp == 0) {
            return IDENTIFIER;
        }
    
        yylval.identifier.unk_00 = curloc;
        return tp;
    }
    return IDENTIFIER;
}

int scan(void) {
    char c;
    char c1;
    int lineNo;
    int hasFilename;    

restart:
    curloc = (int)(inbuf_ptr - input_buffer) + offset_in_file - 1;
    c = input();
label2:
    switch (c) {
        case 0:
            inbuf_ptr--;
            return 0;
        case '\n':
            c = input();
            while (c == ' ' || c == '\t') {
                c = input();
            }
            if (c == '#') {
                curloc = (int)(inbuf_ptr - input_buffer) + offset_in_file - 1;
                if (scan_line_directive(&lineNo, token, &hasFilename) != 1) {
                    c = '\n';
                    goto label2;
                }
                
                if (hasFilename) {
                    register_file(token, lineNo);
                } else {
                    register_file(NULL, lineNo);
                }

                if (hasFilename) {
                    while (c = input()) {
                        if (c == '\n') {
                            goto label2;
                        }
                    }
                }
                c = '\n';
                goto label2;
            }            
            unput();
            /* fallthrough */
        case '\t':
        case '\v':
        case '\f':
        case ' ':
            goto restart;        
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            unput();
            return scan_number(FALSE);
        case '"':
            return scan_string();
        case '\'':
            return scan_char();
        case '(':
        case ')':
        case ',':
        case ';':
        case '?':
        case '[':
        case ']':
        case '{':
        case '}':
        case '~':
            yylval.loc = curloc;
            return c;
        case ':':
            if (options[OPTION_CPLUSPLUS]) {
                c = input();
                if (c == ':') {
                    c = input();
                    if (c == '*') {
                        yylval.loc = curloc;
                        return COLCOLSTAR;
                    }
                    if (c == ' ' || c == '\t') {
                        while (c1 = input()) {
                            if (c1 != ' ' && c1 != '\t') {
                                break;
                            }
                        }
                        if (c1 == '*') {
                            yylval.loc = curloc;
                            return COLCOLSTAR;
                        }
                        unput();
                        yylval.loc = curloc;
                        return COLONCOLON;
                    }
                    unput();
                    yylval.loc = curloc;
                    return COLONCOLON;
                }
                unput();
            }
            yylval.loc = curloc;
            return ':';
        case '+':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return ADD_ASSIGN;
            }
            if (c == '+') {
                yylval.loc = curloc;
                return INC_OP;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, LEVEL_DEFAULT, curloc, "+=");
                    yylval.loc = curloc;
                    return ADD_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '+';
        case '-':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return SUB_ASSIGN;
            }
            if (c == '-') {
                yylval.loc = curloc;
                return DEC_OP;
            }
            if (c == '>') {
                if (options[OPTION_CPLUSPLUS]) {
                    c = input();
                    if (c == '*') {
                        yylval.loc = curloc;
                        return MEMPTR_OP;
                    }
                    unput();
                    yylval.loc = curloc;
                    return PTR_OP;
                }
                yylval.loc = curloc;
                return PTR_OP;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, LEVEL_DEFAULT, curloc, "-=");
                    yylval.loc = curloc;
                    return SUB_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '-';
        case '/':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return DIV_ASSIGN;
            }
            if (c == '*') {
                while (TRUE) {
                    c = input();
                    if (c == '*') {
                        c = input();
                        if (c == '/') {
                            break;
                        }
                        unput();
                    } else if (c == 0) {
                        error(0x20017, LEVEL_ERROR, curloc, c);
                        break;
                    }
                }
                goto restart;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, LEVEL_DEFAULT, curloc, "/=");
                    yylval.loc = curloc;
                    return DIV_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '/';
        case '%':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return REM_ASSIGN;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, LEVEL_DEFAULT, curloc, "%=");
                    yylval.loc = curloc;
                    return REM_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '%';
        case '&':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return AND_ASSIGN;
            }
            if (c == '&') {
                yylval.loc = curloc;
                return AND_OP;
            }
            if (!IS_ANSI) {
                if (c == ' ' || c == '\t') {
                    while (c1 = input()) {
                        if (c1 != ' ' && c1 != '\t') {
                            break;
                        }
                    }
    
                    if (c1 == '=') {
                        error(0x20111, LEVEL_DEFAULT, curloc, "&=");
                        yylval.loc = curloc;
                        return AND_ASSIGN;
                    }
                }
            }
            unput();
            yylval.loc = curloc;
            return '&';
        case '|':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return OR_ASSIGN;
            }
            if (c == '|') {
                yylval.loc = curloc;
                return OR_OP;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, LEVEL_DEFAULT, curloc, "|=");
                    yylval.loc = curloc;
                    return OR_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '|';
        case '^':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return XOR_ASSIGN;
            }
            if (c == ' ' || c == '\t') {
                while (c1 = input()) {
                    if (c1 != ' ' && c1 != '\t') {
                        break;
                    }
                }

                if (c1 == '=') {
                    error(0x20111, LEVEL_DEFAULT, curloc, "^=");
                    yylval.loc = curloc;
                    return XOR_ASSIGN;
                }
            }
            unput();
            yylval.loc = curloc;
            return '^';
        case '!':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return NE_OP;
            }
            unput();
            yylval.loc = curloc;
            return '!';
        case '=':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return EQ_OP;
            }
            unput();
            yylval.loc = curloc;
            return '=';
        case '*':
            c = input();
            if (c == '=') {
                yylval.loc = curloc;
                return MUL_ASSIGN;
            }
            if (!IS_ANSI) {
                if (c == ' ' || c == '\t') {
                    while (c1 = input()) {
                        if (c1 != ' ' && c1 != '\t') {
                            break;
                        }
                    }
    
                    if (c1 == '=') {
                        error(0x20111, LEVEL_DEFAULT, curloc, "*=");
                        yylval.loc = curloc;
                        return MUL_ASSIGN;
                    }
                }
            }
            unput();
            yylval.loc = curloc;
            return '*';
        case '.':
            c = input();
            if (c == '.') {
                c = input();
                if (c == '.') {
                    yylval.loc = curloc;
                    return ELLIPSIS;
                }
                unput();
                yylval.loc = curloc;
                return 0x2E2E; // '..'
            }
            if (c == '*' && options[OPTION_CPLUSPLUS]) {
                yylval.loc = curloc;
                return MEMDOT_OP;
            }
            if (isdigit(c)) {
                unput();
                return scan_number(TRUE);
            }
            unput();
            yylval.loc = curloc;
            return '.';
        case '<':
            c = input();
            if (c == '<') {
                c = input();
                if (c == '=') {
                    yylval.loc = curloc;
                    return LEFT_ASSIGN;
                }
                if (c == ' ' || c == '\t') {
                    while (c1 = input()) {
                        if (c1 != ' ' && c1 != '\t') {
                            break;
                        }
                    }
    
                    if (c1 == '=') {
                        error(0x20111, LEVEL_DEFAULT, curloc, "<<=");
                        yylval.loc = curloc;
                        return LEFT_ASSIGN;
                    }
                }
                unput();
                yylval.loc = curloc;
                return LEFT_OP;
            }
            if (c == '=') {
                yylval.loc = curloc;
                return LE_OP;
            }
            unput();
            yylval.loc = curloc;
            return '<';
        case '>':
            c = input();
            if (c == '>') {
                c = input();
                if (c == '=') {
                    yylval.loc = curloc;
                    return RIGHT_ASSIGN;
                }
                if (c == ' ' || c == '\t') {
                    while (c1 = input()) {
                        if (c1 != ' ' && c1 != '\t') {
                            break;
                        }
                    }
    
                    if (c1 == '=') {
                        error(0x20111, LEVEL_DEFAULT, curloc, ">>=");
                        yylval.loc = curloc;
                        return RIGHT_ASSIGN;
                    }
                }
                unput();
                yylval.loc = curloc;
                return RIGHT_OP;
            }
            if (c == '=') {
                yylval.loc = curloc;
                return GE_OP;
            }
            unput();
            yylval.loc = curloc;
            return '>';
        case 'L':
            c = input();
            if (c == '"') {
                return scan_wstring();
            }
            if (c == '\'') {
                return scan_wchar();
            }
            unput();
            return scan_identifier('L');
        case '$':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '_':
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            if (c == '$' && options[OPTION_DOLLAR] || c != '$') {
                return scan_identifier(c);
            }
            /* fallthrough */
        default:
            if (isprint(c)) {
                error(0x2000C, LEVEL_DEFAULT, curloc, c);
            } else {
                error(0x2000D, LEVEL_DEFAULT, curloc, c);
            }
            goto restart;
    }
}

#ifdef NON_MATCHING
// url: https://decomp.me/scratch/9YiHT
// score: 16(99.95%)
int cpp_line_ptr(char* arg0, char* arg1, int arg2) {
    char* vv;
    int sp58;
    int var_a0;
    int sp50;
    int sp4C;
    unsigned int var_a1;
    int var_v1;
    int var_v0_2;
    char* var_a3;
    int unused1;
    int unused2;
    int var_s0;    
    char* var_v0;
    
    sp58 = (arg1 - arg0) / 2;
    var_a1 = loc_to_cppline(arg2);
    var_s0 = cpplinearr.loc[var_a1].offset;
    
    if (var_s0 == arg2 && var_a1 == cppline) {
        var_a1--;
        arg2--;
        var_s0 = cpplinearr.loc[var_a1].offset;
    }
    if (arg2 - var_s0 > (arg1 - arg0) / 3) {
        sp50 = arg2 - var_s0 - (arg1 - arg0) / 3;
    } else {
        sp50 = 0;
    }
    var_a0 = 1;
    if (var_a1 == cppline || var_s0 < offset_in_file || offset_in_file + BUFFER_SIZE < var_s0) {
        var_a0 = 0;
    }
    if (var_a0 != 0 && (cpplinearr.loc[var_a1 + 1].offset < offset_in_file || offset_in_file + BUFFER_SIZE < cpplinearr.loc[var_a1 + 1].offset)) {
        var_a0 = 0;
    }
    *arg0 = ' ';
    var_a3 = arg0 + 1;   
    
    if (sp50 != 0) {
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = ' ';
        arg0 += 5;
    }
    
    
    if (var_a0 || input_file_status == 1) {
        var_v0 = input_buffer + var_s0 - offset_in_file + 1;
        for (var_v1 = 0; var_v1 < sp50; var_v1++) {
            var_v0++;
        }
        while (*var_v0 != 0 && *var_v0 != '\n' && var_a3 - arg0 <= sp58) {
            if (var_a3 - arg0 < sp58) {
                *var_a3++ = *var_v0++;
            } else {
                var_a3[-1] = '.';
                var_a3[-2] = '.';
                var_a3[-3] = '.';
                var_a3[-4] = '.';
                var_a3[-5] = ' ';
                break;
            }
        }
        if (var_a3[-1] != '\n') {
            *var_a3++ = '\n';
        }
    } else {
        if (fseek(input_file, var_s0, 0) != -1) {
            sp4C = 0;
            while ((var_v0_2 = fgetc(input_file)) != -1) {
                if (sp4C < sp50) {
                    sp4C++;
                } else if (var_a3 - arg0 < sp58) {
                    *var_a3++ = var_v0_2;
                    if ((char)var_v0_2 == '\n') {
                        break;
                    }
                } else {
                    var_a3[-1] = '\n';
                    var_a3[-2] = '.';
                    var_a3[-3] = '.';
                    var_a3[-4] = '.';
                    var_a3[-5] = '.';
                    var_a3[-6] = ' ';                    
                    break;
                }
            }
        }
    }
    
    *var_a3++ = ' ';    
    if (sp50 != 0) {
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = '.';
        *var_a3++ = ' ';
    }
    
    vv = arg0 + 1;
    while (var_s0 < arg2 - sp50) {
        if (*vv == '\n') {
            *arg0 = (*vv) * 0; // fake match
            return 0;
        }
        if (*vv == '\t') {
            *var_a3++ = '\t';
        } else {
            *var_a3++ = '-';
        }
        vv++;
        var_s0++;
    }
    
    *var_a3++ = '^';
    *var_a3++ = '\n';
    *var_a3++ = 0;
    return 1;
}
#else
int cpp_line_ptr(char* arg0, char* arg1, int arg2);
#pragma GLOBAL_ASM("asm/7.1/functions/cfe/scan/cpp_line_ptr.s")
#endif


void init_scan(void) {
    long long longmax;
    long long ulongmax;

    pmhandle = mem_start();
    tokenbuf_size = 0x1000;
    tokenbuf_base = Malloc(tokenbuf_size);
    token = tokenbuf_base;
    wstring_base = tokenbuf_base;

    psymb_handle = link_start(pmhandle, sizeof(ParseSymbol));
    isymb_handle = link_start(pmhandle, 0x14);

    mk_parse_symb(string_to_symbol("__builtin_alignof", 17), ALIGNOF, 0);
    mk_parse_symb(string_to_symbol("__builtin_classof", 17), CLASSOF, 0);
    mk_parse_symb(string_to_symbol("__builtin_try", 13), TRY, 0);
    mk_parse_symb(string_to_symbol("__builtin_except", 16), EXCEPT, 0);
    mk_parse_symb(string_to_symbol("__builtin_finally", 17), FINALLY, 0);
    mk_parse_symb(string_to_symbol("__unaligned", 11), UNALIGN, 0);
    mk_parse_symb(string_to_symbol("__builtin_leave", 15), LEAVE, 0);
    mk_parse_symb(string_to_symbol("auto", 4), AUTO, 0);
    mk_parse_symb(string_to_symbol("break", 5), BREAK, 0);
    mk_parse_symb(string_to_symbol("char", 4), CHAR, 0);
    mk_parse_symb(string_to_symbol("case", 4), CASE, 0);
    mk_parse_symb(string_to_symbol("const", 5), CONST, 0);
    mk_parse_symb(string_to_symbol("continue", 8), CONTINUE, 0);
    mk_parse_symb(string_to_symbol("double", 6), DOUBLE, 0);
    mk_parse_symb(string_to_symbol("default", 7), DEFAULT, 0);
    mk_parse_symb(string_to_symbol("do", 2), DO, 0);
    mk_parse_symb(string_to_symbol("extern", 6), EXTERN, 0);
    mk_parse_symb(string_to_symbol("else", 4), ELSE, 0);
    mk_parse_symb(string_to_symbol("enum", 4), ENUM, 0);
    mk_parse_symb(string_to_symbol("for", 3), FOR, 0);
    mk_parse_symb(string_to_symbol("float", 5), FLOAT, 0);
    mk_parse_symb(string_to_symbol("goto", 4), GOTO, 0);
    mk_parse_symb(string_to_symbol("if", 2), IF, 0);
    mk_parse_symb(string_to_symbol("int", 3), INT, 0);
    mk_parse_symb(string_to_symbol("long", 4), LONG, 0);
    mk_parse_symb(string_to_symbol("__long_long", 11), LONGLONG, 0);
    mk_parse_symb(string_to_symbol("return", 6), RETURN, 0);
    mk_parse_symb(string_to_symbol("register", 8), REGISTER, 0);
    mk_parse_symb(string_to_symbol("switch", 6), SWITCH, 0);
    mk_parse_symb(string_to_symbol("struct", 6), STRUCT, 0);
    mk_parse_symb(string_to_symbol("signed", 6), SIGNED, 0);
    mk_parse_symb(string_to_symbol("sizeof", 6), SIZEOF, 0);
    mk_parse_symb(string_to_symbol("short", 5), SHORT, 0);
    mk_parse_symb(string_to_symbol("static", 6), STATIC, 0);
    mk_parse_symb(string_to_symbol("typedef", 7), TYPEDEF, 0);
    mk_parse_symb(string_to_symbol("unsigned", 8), UNSIGNED, 0);
    mk_parse_symb(string_to_symbol("union", 5), UNION, 0);
    mk_parse_symb(string_to_symbol("void", 4), VOID, 0);
    mk_parse_symb(string_to_symbol("volatile", 8), VOLATILE, 0);
    mk_parse_symb(string_to_symbol("while", 5), WHILE, 0);
    mk_parse_symb(string_to_symbol("__builtin_alignof", 17), ALIGNOF, 0);
    mk_parse_symb(string_to_symbol("__pragma", 8), __PRAGMA, 0);
    if (!options[OPTION_CPLUSPLUS] && !(options[OPTION_ANSI_MODE] & 1) || !options[OPTION_CPLUSPLUS] && (options[OPTION_ANSI_MODE] & 3) == 3) {
        mk_parse_symb(string_to_symbol("__inline", 8), INLINE, 0);
    }
    if (options[OPTION_CPLUSPLUS]) {
        mk_parse_symb(string_to_symbol("class", 5), CLASS, 0);
        mk_parse_symb(string_to_symbol("virtual", 7), VIRTUAL, 0);
        mk_parse_symb(string_to_symbol("protected", 9), PROTECTED, 0);
        mk_parse_symb(string_to_symbol("public", 6), PUBLIC, 0);
        mk_parse_symb(string_to_symbol("private", 7), PRIVATE, 0);
        mk_parse_symb(string_to_symbol("operator", 8), OPERATOR, 0);
        mk_parse_symb(string_to_symbol("this", 4), THIS, 0);
        mk_parse_symb(string_to_symbol("new", 3), NEW, 0);
        mk_parse_symb(string_to_symbol("delete", 6), DELETE, 0);
        mk_parse_symb(string_to_symbol("inline", 6), INLINE, 0);
        mk_parse_symb(string_to_symbol("friend", 6), FRIEND, 0);
    }

    fill_input_buffer();
    
    longmax = LONG_MAX;
    ulongmax = 1 + longmax * 2;
    __LONGLONG_MAX = ulongmax + longmax * 2 * (longmax + 1);
    __ULONGLONG_MAX = __LONGLONG_MAX * 2 + 1;
    __LONGLONG_MIN = -__LONGLONG_MAX - 1;
}

ParseSymbol* mk_parse_symb(Symbol* symb, int id, int arg2) {
    ParseSymbol* psymb;
    ParseSymbol* prev;
    
    psymb = (ParseSymbol*)get_link_elem(psymb_handle);
    psymb->unk_04 = id;
    psymb->unk_08 = arg2;
    prev = (ParseSymbol*)(psymb->link.next = (LinkedListEntry*)symb->unk_04);
    symb->unk_04 = psymb;

    if (debug_arr['P'] > 0) {
        fprintf(dbgout, "creating %.*s (0x%x:%d:%s) hides (0x%x:%d:%s)\n",
            symb->namelen, symb->name,
            psymb, psymb->unk_08, GET_SYM_CAT(psymb->unk_04),
            prev, prev != NULL ? prev->unk_08 : -1, prev != NULL ? GET_SYM_CAT(prev->unk_04) : "<nil>");
    }

    return psymb;
}