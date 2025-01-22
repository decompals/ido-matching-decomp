#ifndef REPORT_H
#define REPORT_H
#include "common.h"
procedure report_error(error_kind: ugen_report; line: CARDINAL; internal_file: String; error: String); external;
#endif /* REPORT_H */
