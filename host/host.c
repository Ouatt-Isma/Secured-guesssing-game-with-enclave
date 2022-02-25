#include <openenclave/host.h>
#include <stdio.h>

#include "guessing_game_u.h"

//Global variables


bool check_simulate_opt(int* argc, const char* argv[])
{
    for (int i = 0; i < *argc; i++)
    {
        if (strcmp(argv[i], "--simulate") == 0)
        {
            fprintf(stdout, "Running in simulation mode\n");
            memmove(&argv[i], &argv[i + 1], (*argc - i) * sizeof(char*));
            (*argc)--;
            return true;
        }
    }
    return false;
}

int main(int argc, const char* argv[])
{
    oe_result_t result;
    int ret = 1;
    oe_enclave_t* enclave = NULL;

    uint32_t flags = OE_ENCLAVE_FLAG_DEBUG;
    if (check_simulate_opt(&argc, argv))
    {
        flags |= OE_ENCLAVE_FLAG_SIMULATE;
    }

    if (argc != 2)
    {
        fprintf(
            stderr, "Usage: %s enclave_image_path [ --simulate  ]\n", argv[0]);
        goto exit;
    }

    // Create the enclave
    result = oe_create_guessing_game_enclave(
        argv[1], OE_ENCLAVE_TYPE_AUTO, flags, NULL, 0, &enclave);
    if (result != OE_OK)
    {
        fprintf(
            stderr,
            "oe_create_guessing_game_enclave(): result=%u (%s)\n",
            result,
            oe_result_str(result));
        goto exit;
    }

    // Call into the enclave
   
    int userint = -1;
    int maxnum = -1;
    printf("enter a max value\n");
    scanf("%d", &maxnum);
    printf("max value: %d\n", maxnum);
    result = enc_get_maxnum(enclave, maxnum);
        if (result != OE_OK)
        {
        fprintf(
            stderr,
            "calling into enc_get_maxnum failed: result=%u (%s)\n",
            result,
            oe_result_str(result));
        goto exit;
        }
    int* res = malloc(sizeof(int)); 
    int cpt = 0;
     
    //uncomment next line and comment the one after to test
    //the lock it self
    //for ( cpt=0; cpt<maxnum+1; cpt++){
    for ( cpt=0; cpt<maxnum; cpt++){
    	printf("enter a guess value\n");
        scanf("%d", &userint);
        printf("you entered: %d\n", userint);
		
	result = enc_compare(enclave, userint, res);
    	if (result != OE_OK)
    	{ 
	if (result!=OE_ENCLAVE_ABORTING){
        fprintf(
            stderr,
            "calling enc_compare into enclave failed: result=%u (%s)\n",
            result,
            oe_result_str(result));
        goto exit;
	}
	else{
	fprintf(
            stderr,
            "Enclave aborted\nYou lost");
	ret = 0;
	goto exit; 
	}
    	}
	if(*res){
		printf("You won!\n"); 
		break;
	}
	else{
		printf("Wrong guess!\n");

	}
    }
    ret = 0;
exit:
    // Clean up the enclave if we created one
    if (enclave)
        oe_terminate_enclave(enclave);

    return ret;
}
