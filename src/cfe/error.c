#ifdef __GNUC__
// workaround to pass gcc check
#define __STDARG_H__
#define va_list int
#define va_start(x, y)
#define va_arg(x, y) (0)
#endif

#include "common.h"

char* ident = "$Header: /hosts/bonnie/proj/irix6.4-ssg/isms/cmplrs/targucode/cfe/RCS/error.c,v 1.9 1994/06/15 00:22:07 rdahl Exp $";

typedef struct ErrorStruct {
    /* 0x00 */ struct LinkedListEntry link;
    /* 0x04 */ int message;
    /* 0x08 */ int level;
    /* 0x0C */ int location;
    /* 0x10 */ char* params[4];
} ErrorStruct; // size = 0x20

static int default_error_levels[7][3] = {
    { LEVEL_ERROR, LEVEL_ERROR, LEVEL_ERROR },
    { LEVEL_WARNING, LEVEL_WARNING, LEVEL_WARNING },
    { LEVEL_FATAL, LEVEL_FATAL, LEVEL_FATAL },
    { LEVEL_WARNING, LEVEL_ERROR, LEVEL_WARNING },
    { LEVEL_SUPPRESSED, LEVEL_SUPPRESSED, LEVEL_SUPPRESSED },
    { LEVEL_SUPPRESSED, LEVEL_WARNING, LEVEL_WARNING },
    { LEVEL_SUPPRESSED, LEVEL_ERROR, LEVEL_ERROR },
};

/* .data      */
static FILE* D_1001BA78 = stderr; // not sure if it's correct value

/* .bss       */
/* 0x10020F20 */ static char** message_files;
/* 0x10020F24 */ static int num_messages;
/* 0x10020F28 */ static FILE* current_mesg_file;
/* 0x10020F2C */ static MemCtx* error_handle;
/* 0x10020F30 */ static LinkedList* error_list;
/* 0x10020F34 */ static int unused;
/* 0x10020F38 */ static char error_buffer[3072];
/* 0x10021B38 */ static char B_10021B38[1024];
/* 0x10021F38 */ static char message_text_buf[4096];
/* 0x10022F38 */ static int B_10022F38[8];
/* 0x10022F58 */ static int error_already_reported[358];
/* 0x100234F0 */ static int warning_disabled[357];

int set_woff(int warning_number) {
    if (warning_number < 500 || warning_number >= 857 || act_to_imp[warning_number - 500] == -1) {
        return FALSE;
    }

    warning_disabled[act_to_imp[warning_number - 500]] = TRUE;
    return TRUE;
}

int error_init(char** msg_files, FILE* file, int error_mode) {
    if (msg_files != NULL) {
        message_files = msg_files;
    }
    if (file != NULL) {
        D_1001BA78 = file;
    }
    mode = error_mode;
    num_messages = 0;
    current_mesg_file = NULL;
    error_handle = mem_start();
    error_list = link_start(error_handle, sizeof(ErrorStruct));
    return 1;
}

void set_error_mode(int error_mode) {
    mode = error_mode;
}

static void get_error_message(char* buffer, int msgid, int type) {
    int offset;
    size_t length;
    int i;

    if (current_mesg_file == NULL) {
        while (*message_files != NULL && current_mesg_file == NULL) {
            current_mesg_file = fopen(*message_files, "r");
            if (debug_arr['e'] > 0) {
                fprintf(dbgout, "attempting to open msg file %s %s\n", *message_files, current_mesg_file != NULL ? "success" : "failed");
            }
            message_files++;
        }

        if (current_mesg_file == NULL) {
err:
            current_mesg_file = NULL;
            sprintf(buffer, "ERROR MESSAGE %d", msgid);        
            return;
        }
        if (fgetc(current_mesg_file) != '@' || fscanf(current_mesg_file, "%d %d %d", &num_messages, &num_messages, &num_messages) != 3) {
            goto err;
        }
        
        short_offset = mem_alloc(error_handle, (unsigned int)(num_messages * 4), 4);
        long_offset = mem_alloc(error_handle, (unsigned int)(num_messages * 4), 4);
        ansi_offset = mem_alloc(error_handle, (unsigned int)(num_messages * 4), 4);

        for (i = 0; i < num_messages; i++) {
            if (fscanf(current_mesg_file, "%ld %ld %ld", &short_offset[i], &long_offset[i], &ansi_offset[i]) != 3) {
                goto err;
            }
        }
        num_messages--;
        if (num_messages != 357) {
            goto err;
        }
    }

    if (msgid < num_messages) {
        switch (type) {
            case 0:
                offset = short_offset[msgid];
                length = long_offset[msgid] - offset;
                break;
            case 1:
                offset = long_offset[msgid];
                length = ansi_offset[msgid] - offset;
                break;
            case 2:
                offset = ansi_offset[msgid];
                length = short_offset[msgid + 1] - offset;
                break;
        }

        if (fseek(current_mesg_file, offset, SEEK_SET) == -1 || fread(buffer, 1, length, current_mesg_file) != length) {
            goto err;
        }

        if (type != 1) {
            buffer[length != 0 ? length - 1 : length] = 0;
        } else {
            buffer[length] = 0;
        }
    }
}

static void get_warning_message(char* buffer, int msg) {
    sprintf(buffer, "Warning %d: ", imp_to_act[msg & 0xFFFF]);
}

void lint_warning(ErrorStruct* arg0) {
    char* sp3C;
    int sp38 = 0;

    strcpy(error_buffer, "");

    if (arg0->location != -1 && real_file_line(arg0->location, &sp3C, &sp38, 0) == 1) {
        if (sp3C != 0) {
            error(0x170154, LEVEL_6, -1, sp3C);
            error(0x170155, LEVEL_6, -1);
        }
        if (sp38 != 0) {
            sprintf(error_buffer, "(%d)  ", sp38);
        }
    }

    switch (arg0->level) {
        case 1:
            get_warning_message(message_text_buf, arg0->message);
            strcat(error_buffer, message_text_buf);
            break;
        case 3:
            get_error_message(message_text_buf, 5, 0);
            strcat(error_buffer, message_text_buf);
            break;
        case 2:
            get_error_message(message_text_buf, 8, 0);
            strcat(error_buffer, message_text_buf);
            break;
    }

    get_error_message(message_text_buf, arg0->message & 0xFFFF, 0);
    sprintf(error_buffer + strlen(error_buffer), message_text_buf, arg0->params[0], arg0->params[1], arg0->params[2], arg0->params[3]);
    strcat(error_buffer, "\n");
    fprintf(D_1001BA78, "%s", error_buffer);
}

static void print_error(ErrorStruct* arg0) {
    char* file;
    int line = 0;
    

    if ((arg0->message >> 20) != 0 && error_already_reported[arg0->message & 0xFFFF]) {
        return;
    }
    error_already_reported[arg0->message & 0xFFFF] = TRUE;

    if (options[OPTION_LINT_FLAGS] && !(options[OPTION_VERBOSITY] & VERBOSE_FLAG_20)) {
        lint_warning(arg0);
        return;
    }

    strcpy(error_buffer, "");
    if (myname != NULL) {
        strcat(error_buffer, myname);
        strcat(error_buffer, ": ");
    }

    switch (arg0->level) {
        case 1:
            get_warning_message(message_text_buf, arg0->message);
            strcat(error_buffer, message_text_buf);
            break;
        case 3:
            get_error_message(message_text_buf, 5, 0);
            strcat(error_buffer, message_text_buf);
            break;
        case 2:
            get_error_message(message_text_buf, 8, 0);
            strcat(error_buffer, message_text_buf);
            break;
    }

    if (arg0->location != -1 && real_file_line(arg0->location, &file, &line, 0) == 1) {
        if (file != NULL) {
            strcat(error_buffer, file);
            strcat(error_buffer, ", ");
        }
        if (line != 0) {
            get_error_message(message_text_buf, 3, 0);
            strcat(error_buffer, message_text_buf);
            sprintf(error_buffer + strlen(error_buffer), " %d: ", line);
        }
    }
    get_error_message(message_text_buf, arg0->message & 0xFFFF, 0);
    sprintf(error_buffer + strlen(error_buffer), message_text_buf, arg0->params[0], arg0->params[1], arg0->params[2], arg0->params[3]);
    if (IS_STRICT_ANSI) {
        get_error_message(message_text_buf, arg0->message & 0xFFFF, 2);
        if (strlen(message_text_buf) != 0) {
            sprintf(error_buffer + strlen(error_buffer), " (%s)\n", message_text_buf);
        } else {
            strcat(error_buffer, "\n");
        }
    } else {
        strcat(error_buffer, "\n");
    }

    if ((options[OPTION_VERBOSITY] & VERBOSE_FLAG_2) && file != NULL && line != 0) {
        cpp_line_ptr(error_buffer + strlen(error_buffer), B_10021B38, arg0->location);
    }
    if (options[OPTION_VERBOSITY] & VERBOSE_FLAG_4) {
        get_error_message(error_buffer + strlen(error_buffer), arg0->message & 0xFFFF, 1);
    }
    fprintf(D_1001BA78, "%s", error_buffer);
}

void error_flush(int arg0) {
    while (error_list->used_list != NULL) {
        if (arg0 < ((ErrorStruct*)error_list->used_list)->location && arg0 != -1) {
            break;
        }
        print_error(((ErrorStruct*)error_list->used_list));
        link_pop(error_list);
    }
}

int error(int message, enum ErrorLevels level, int location, ...) {
    int real_level;
    ErrorStruct* ers;
    int print_immediately = imm_flag;
    int i;
    int msgid = message & 0xFFFF;
    static int isFlushing = FALSE;
    int unused;

    if (msgid > 356) {
        real_level = LEVEL_FATAL;
    } else if (level == LEVEL_DEFAULT) {
        real_level = default_error_levels[err_options[msgid]][mode];
    } else {
        real_level = level;
    }

    if (real_level == LEVEL_SUPPRESSED) {
        return LEVEL_SUPPRESSED;
    }

    if (real_level == LEVEL_WARNING) {
        if (!(options[OPTION_VERBOSITY] & VERBOSE_FLAG_1) || warning_disabled[msgid]) {
            return LEVEL_SUPPRESSED;
        }
        num_warns++;
    }

    if (debug_arr['e'] > 0) {
        fprintf(dbgout, "err_msg #:%d l:%d loca:%x sec:%d\n", msgid, real_level, location, (message >> 16) & 0xF);
    }

    ers = get_link_elem(error_list);
    if (msgid < 0x165) {
        if (err_fmts[msgid].unk_00 != 0) {
            va_list args;
            va_start(args, location);
            for (i = 0; i < err_fmts[msgid].unk_00; i++) {
                switch(fmts_arr[err_fmts[msgid].unk_02 + i].unk_04) {
                    case 1:
                        sprintf(error_buffer, fmts_arr[err_fmts[msgid].unk_02 + i].unk_00, va_arg(args, int));
                        break;
                    case 3:
                        sprintf(error_buffer, fmts_arr[err_fmts[msgid].unk_02 + i].unk_00, va_arg(args, double));
                        break;
                    case 2:
                        sprintf(error_buffer, fmts_arr[err_fmts[msgid].unk_02 + i].unk_00, va_arg(args, char*));
                        break;
                }
    
                ers->params[i] = mem_alloc(error_handle, strlen(error_buffer) + 1, 1);
                strcpy(ers->params[i], error_buffer);
            }
        }
    }

    ers->message = message;
    ers->level = real_level;
    ers->location = location;

    if (real_level == LEVEL_FATAL || real_level == LEVEL_6) {
        print_immediately = TRUE;
    }
    if (location == -1) {
        print_immediately = TRUE;
    }

    if (print_immediately) {
        print_error(ers);
    } else {
        LinkedListEntry* a0 = (LinkedListEntry*)error_list;
        LinkedListEntry* v0 = error_list->used_list;
        while (v0 != NULL) {
            if (ers->location < ((ErrorStruct*)v0)->location) {
                ers->link.next = v0;
                break;
            }
            a0 = v0;
            v0 = v0->next;
        }
        a0->next = &ers->link;
    }

    if (real_level == LEVEL_FATAL) {
        fatal();
    }

    if (real_level == LEVEL_ERROR) {
        int v1 = (message >> 16) & 0xF;
        num_errs++;

        if (v1 != 0 && v1 < 8) {
            B_10022F38[v1 - 1]++;
        } else {
            ((void)((!v1)||__assert("!i", "error.c", 471)));
        }
    }

    if (num_errs >= 30 && !isFlushing) {
        isFlushing = TRUE;
        error_flush(-1);
        isFlushing = FALSE;
        error(0x40007, LEVEL_FATAL, -1);
    }

    return real_level;
}