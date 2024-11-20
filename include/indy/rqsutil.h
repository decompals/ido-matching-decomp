#ifndef _RQSUTIL_H
#define _RQSUTIL_H 1
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>

extern int machine_64;


typedef struct {
    time_t timestamp;
        /* timestamp to be used to mark requickstarted objects -
           by default set to the time that struct is initialized */
    int doit;
        /* TRUE if you actually want to run the command - default = TRUE */
    char *check_registry;
        /* path to so_locations file to find location information - default = NULL */
    char *update_registry;
        /* path to so_locations file that will be updated when objects are requickstarted - default = NULL*/
    int echo_cmd;
        /* Set to TRUE if you want the command to be echoed before execution - default = TRUE*/
    int force;
        /* Set to TRUE if you want to try to force the requickstarting of objects that are marked as non-quickstart - default = FALSE*/
    int do_warnings;
        /* Print out warnings as you do requickstart - default = TRUE */
    int print_reason;
        /* print out the reason an object can't re requickstarted - default = FALSE */
    char *rqs_cmd;
        /* The path of the rqs command - default = /usr/etc/rqs */
    char *input_file;
        /* The path of the so information file - default = NULL */
    char *output_file;
        /* The path of a new so information file that contains the state of the objects after requickstart - default = NULL */
    int rescan;
       /* TRUE if you want to rescan the objects before determining whether things must be requickstarted - default = FALSE */
    int rqs_update_registry;
       /* TRUE if you want to update the so_locations file - default = FALSE */
    struct registry_info *registry;
       /* Internal */
    int (*rqs_callback)(char* filename, char *real_file_name);
       /* Routine to call after file has been successfully requickstarted */
    int (*rqs_pre_callback)(char* filename, char *real_file_name);
       /* Routine to call before file has been successfully requickstarted */
    int (*rqs_fail_callback)(char* filename, char *real_file_name);
       /* Routine to call after file has been unsuccessfully requickstarted */
    char *rqs_error_log;
       /* name of file to pass to rqs as error log file */
    FILE *list_file;
        /* pointer to file that will contain a list of all the
	  files that have been successfully requickstarted */
    FILE *inst_file;
        /* pointer to file that is used to write out ins specific information */
    char *rld_file_name;    /* name of rld file to pick up address of rld_text_resolve */
    char	*file_to_requickstart;	/* name of file to specifically requickstart */
    int rqs_error;  /* set to 1 if rqs panics */
    char *check_registry_64;
        /* path to 64 bit so_locations file to find location information - default = NULL */
    char *update_registry_64;
        /* path to 64 bit so_locations file that will be updated when objects are requickstarted - default = NULL*/
    char *update_registry_path;
    char *check_registry_path;
        /* top path to all the so_locations file e.g /usr, which specifies
	 * /usr/lib/so_locations for 32 bit objects and
   	 * /usr/lib64/so_locations for 64 bit objects
	 */
} rqs_info;

/*
  Retrieves the rqs information from that file given by
  initial_filename.  real_filename gives the final
  location for the file (in case it gets moved).
  cwd gives the current working directory, used for relative
  path names.  outfile points to the output file where
  the information is stored.
*/

extern void process_file(char *initial_filename, char *real_filename, char *cwd, FILE *outfile);

/*
  Opens an output file that contains the shared object
  information.  If append is TRUE then the file will be
  openned in append mode. Locks the file while it is
  openned.
*/

extern FILE *open_so_file(char *filename, int append);

/*
  Closes the output file, including releasing the lock
*/

extern void close_so_file(FILE *outfile);

/*
  Retrieves the rqs information from the file given by
  filename, with real_filename, and cwd as defined in
  process_file.  Writes the information in the file
  given by outfilename, appending it if append is TRUE.
*/

extern void process_file_into_file(char *filename, char *real_filename, char *cwd, char *outfilename, int append);


/*
  Sets the ROOT to be appended to paths when computing
  when the computing rqs state for the recorded objects
*/

extern void set_rqs_root(char *rqs_root);

/*
  Sets the value to be prepended to pathnames in the so.list
  file when the computing pathnames for the recorded object
*/

extern void set_rqs_prefix(char *rqs_prefix);

/*
  Initializes rqs_info structure
*/
extern void initialize_rqs_info(rqs_info *info);

/*
  Causes requickstart to be done on list of objects given
  in lib_vec, using the rqs_info passed in by info
*/

extern void do_requickstart_from_lib_vec(struct library_vec *lib_vec, rqs_info *info);

/*
  Causes requickstart to be done on objects found in the
  file info->input_file.
*/
  
extern int do_requickstart_from_file(rqs_info *info);

extern int is_64bit_machine(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _RQSUTIL_H */



