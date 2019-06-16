#include "globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE FALSE

/* set NO_CODE to TRUE to get a compiler that does not
 * generate code
 */
#define NO_CODE FALSE

#include "util.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#if !NO_ANALYZE
#include "analyze.h"
#if !NO_CODE
#include "cgen.h"
#include "code.h"
#endif
#endif
#endif

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;
FILE * data;
FILE * code_r;
FILE * data_r;
FILE * complete;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

int main( int argc, char * argv[] )
{ TreeNode * syntaxTree;
  DecoNode * decoTree;
  char pgm[120]; /* source code file name */
  if (argc != 2)
    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }
  strcpy(pgm,argv[1]) ;
  if (strchr (pgm, '.') == NULL)
     strcat(pgm,".tny");
  source = fopen(pgm,"r");
  if (source==NULL)
  { fprintf(stderr,"File %s not found\n",pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  //fprintf(listing,"\nTINY COMPILATION: %s\n",pgm);
#if NO_PARSE
  if(TraceScan)
  {
    fprintf(listing, "   line number\t\ttoken\t\tlexeme\n");
    fprintf(listing, "--------------------------------------------------\n");
  }
  while (getToken()!=ENDFILE);
#else
  syntaxTree = parse();
  if (TraceParse) {
    if(!Error) fprintf(listing,"\nSyntax tree:\n");
    printTree(syntaxTree);
  }
#if !NO_ANALYZE
  if (! Error)
  { //if (TraceAnalyze) fprintf(listing,"\nBuilding Symbol Table...\n");
    buildSymtab(syntaxTree);
    //if (TraceAnalyze) fprintf(listing,"\nChecking Types...\n");
    if(! Error) typeCheck(syntaxTree);
    //if (TraceAnalyze) fprintf(listing,"\nType Checking Finished\n");
  }
#if !NO_CODE
  if (! Error)
  {
    decoTree = copyTree(syntaxTree);
    printDecoTree(decoTree, 0);

    char * code_name;
    char * data_name;
    char * complete_name;
    char tmp_str[100];

    int fnlen = strcspn(pgm,".");
    code_name = (char *) calloc(fnlen+7, sizeof(char));
    data_name = (char *) calloc(fnlen+7, sizeof(char));
    complete_name = (char *) calloc(fnlen+7, sizeof(char));
    strncpy(code_name, pgm, fnlen);
    strncpy(data_name, pgm, fnlen);
    strncpy(complete_name, pgm, fnlen);
    strcat(code_name, ".code");
    strcat(data_name, ".data");
    strcat(complete_name, ".s");
    code = fopen(code_name, "w");
    data = fopen(data_name, "w");
    complete = fopen(complete_name, "w");

    if (code == NULL || data == NULL || complete == NULL)
    {
      printf("Unable to open %s or %s or %s\n", code_name, data_name, complete_name);
      exit(1);
    }
    
    initCodeGen();
    codeGen(decoTree);

    code_r = fopen(code_name, "r");
    data_r = fopen(data_name, "r");

    while(fgets(tmp_str, 100, code_r) != NULL) fprintf(complete, "%s", tmp_str);
    fprintf(complete, "\n");
    while(fgets(tmp_str, 100, data_r) != NULL) fprintf(complete, "%s", tmp_str);

    fclose(code);
    fclose(data);
    remove(code_name);
    remove(data_name);
    fclose(complete);
  }
#endif
#endif
#endif
  fclose(source);
  return 0;
}