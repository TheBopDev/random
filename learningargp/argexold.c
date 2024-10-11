/* Author: TheBopDev
 * GitHub: github.com/TheBopDev
 * File created: 
 * File modified:
 */


#include <stdio.h>
#include <argp.h>



const char *argp_program_version = "Testing argp library v0.1";

const char *argp_program_bug_address = "<josh@bop.dev>";

// Used by main to communicate with parse_opt.
struct arguments
{
	char *args[2];		/* ARG1 and ARG2 */
	int verbose;			/* -v */
	char *outfile;		/* -o */
	char *string1, *string2; /* -a and -b */
};



/* Order of fields: {NAME, KEY, ARG, FLAGS, DOC} */
static struct argp_option options[] =
{
	{"verbose", 'v', 0, 0, "Produce verbose output."},
	{"alpha", 'a', "STRING1", 0, "Manipulate STRING1 related to flag -a"},
	{"bravo", 'b', "STRING2", 0, "Manipulate STRING2 related to flag -b"},
	{"output", 'o', "OUTFILE", 0, "Direct output to OUTFILE instead of console"},
	{0}
};


/* Order of fields: KEY, ARG, STATE. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;

	switch (key)
	{
		case 'v':
			arguments->verbose = 1;
			break;
		case 'a':
			arguments->string1 = arg;
			break;
		case 'b':
			arguments->string2 = arg;
			break;
		case 'o':
			arguments->outfile = arg;
			break;
		/* What does this do? */
		case ARGP_KEY_ARG:
			if (state->ARG_NUM >= 2)
				{
					argp_usage(state);
				}
			arguments->args[state->arg_num] = arg;
			break;

		/* What does this do? */
		case ARGP_KEY_END
			if (state->arg_num < 2)
				{
					argp_usage (state)
				}
			break;

		/* Default case */
		default:
			return ARGP_ERR_UNKNOWN;
	}

	// shouldn't ever reach this point.
	return 0;
}



/* What does this mean...? */

/* ARGS_DOC. Field 3 in ARGP.
 * A description of the non-option command-line arguments
 * that we accept.
 */
static char args_doc[] = "ARG1 ARG2";


/* DOC. Field 4 in ARGP.
 * Program documentation"
 */
static char doc[] = "Following along with crasseux.com tutorial";


/* ARGP structure itself */
static struct argp argp = {options, parse_opt, args_doc, doc};




// Now the main function
int main(int argc, char** argv[])
{
	struct arguments arguments;
	FILE *outstream;

	char sampleParagraph[] = "blah blah blah... blah";


	// Init with default arguments
	// TODO: Wrap this in a function call to make main code cleaner.
	arguments.outfile = NULL;
	arguments.string1 = "";
	arguments.string2 = "";
	arguments.verbose = 0;


	// TODO: Look into why this particular structure
	/* argument parsing */
	argp_parse(&argp, argc, argv, 0, 0, &arguments);


	// Did user include an output file?
	if (arguments.outfile)
	{
		outstream = fopen(arguments.outfile, "w");
	}
	else
	{
		outstream = stdout;
	}


	// Print argument values
	fprintf(outstream, "alpha = %s\nbravo = %s\n\n",
			arguments.string1, arguments.string2);

	fprintf(outstream,"ARG1 = %s\nARG2 = %s\n\n",
			arguments.args[0], arguments.args[1]);


	/* If in verbose mode, print this stuff too */
	if (arguments.verbose)
	{
		fprintf(outstream, sampleParagraph);
	}





	return 0;
}

