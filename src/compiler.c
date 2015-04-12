/*
Copyright 2013, 2014 Elbert van de Put

TODO:
add support for module to return more then one variable
*/
#include "compiler.h"

//array to store destination
int _destArray[64];

int _moduleIdArray[8];
int _moduleSize;

guint _quarksoup[64];
guint _soupsize = 0;
char _isoutput = 0;

//checks if the current identifier is a operation
guint32 isOperation(GScanner *scanner, Module *module)
{
    //is it an operation
    if(!g_strcmp0(scanner->value.v_identifier, "and"))
    {
    	module->gates[module->gateSize].type = AND;
        logs_build_update_status(logHandle," and:");
        return 1;
    }
    else if(!g_strcmp0(scanner->value.v_identifier, "or"))
    {
    	module->gates[module->gateSize].type = OR;
     	logs_build_update_status(logHandle,"  or:");
     	return 1;
    }
    else if(!g_strcmp0(scanner->value.v_identifier, "not"))
    {
    	module->gates[module->gateSize].type = NOT;
     	logs_build_update_status(logHandle," not:");
     	return 1;
    }
    else if(!g_strcmp0(scanner->value.v_identifier, "xor"))
    {
    	module->gates[module->gateSize].type = XOR;
        logs_build_update_status(logHandle, " xor:");
		return 1;
    }

    //output
    else if(!g_strcmp0(scanner->value.v_identifier, "out"))
	{
		_isoutput = 1;
		logs_build_update_status(logHandle, "\n\tOut:");
		return 1;
	}

	//module TODO: store module id's in array for easy lookup
    int i;
    int id = g_quark_from_string(scanner->value.v_identifier);
    for(i = 0; i < _moduleSize; i++)
    {
        if(_moduleIdArray[i] == id)
        {
            module->gates[module->gateSize].type = MODULE;
            module->gates[module->gateSize].moduleID = id;
            logs_build_update_status(logHandle, g_strdup_printf(" module[%d]:", id));
            return 1;
        }
    }


	return 0;
}

//searches for arguments (add extensive debugging here)
//mode 0 is input
//mode 1 is destination
//mode 2 is operand
guint32 getArgument(GScanner *scanner, Module *module, int mode)
{
	guint ID;
	static guint dest;
	static gboolean isDest;
	int i, j, k;

	do
	{
		//is the argument valid
    	if(scanner->token == G_TOKEN_IDENTIFIER)
    	{
			//is the argument an operation, only operands
			if(mode != 0 && isOperation(scanner, module))
			{
				//search for arguments
				if(g_scanner_get_next_token(scanner) == G_TOKEN_LEFT_PAREN)
				{
					g_scanner_get_next_token(scanner);
					getArgument(scanner, module, 2);
				}
				else
				{
					logs_build_update_status(logHandle, "Error: operation without arguments\n");
					break;
				}
			}

			//no its not
			else
			{
				ID = g_quark_from_string(scanner->value.v_identifier);

				//input
				if(mode == 0)
				{
					logs_build_update_status(logHandle, g_strdup_printf(" input[%u] ", _soupsize));

					//add to input array
					module->input[module->inputSize++] = _soupsize;

					_quarksoup[_soupsize++] = ID;

				}

				//destination
				else if(mode == 1)
				{
					//does it exist?
					for(i = 0; i < _soupsize; i++)
					{
						if(_quarksoup[i] == ID)
						{
							dest = i;
							isDest = TRUE;
							break;
						}
					}
					//no, so make it
					if(isDest == FALSE)
					{
						dest = _soupsize;
						_quarksoup[_soupsize++] = ID;
						isDest = TRUE;
					}
				}

				//operand (fill gate structure here
				else if(mode == 2)
				{
					int curGate = module->gateSize;

					//add the gates that we have to output to (stores to array)
					if(isDest)
					{
						logs_build_update_status(logHandle, g_strdup_printf(" dest[%d]", dest));
						_destArray[curGate] = dest;
						isDest = FALSE;
					}

					for(i = 0; i < _soupsize; i++)
					{
						if(_quarksoup[i] == ID)
							break;
					}
					logs_build_update_status(logHandle, g_strdup_printf(" op[%u] ", i));

					//is this operand from input?
					for(j = 0; j < module->inputSize; j++)
					{
						if(module->input[j] == i)
						{
							module->inputGate[j][ module->inputGateSize[j]++ ] = module->gateSize;
							break;
						}
					}

					//if we have previously parsed the output statement
					if(_isoutput)
					{
						module->output[ module->outputSize ] = k;

						for(k = 0; k <= curGate; k++)
						{
							if(_destArray[k] == i)
							{
								//outputs are represented as negative numbers
								module->gates[k].output[ module->gates[k].outputSize++ ] = -module->outputSize;
								break;
							}
						}
						module->outputSize++;
					}

					// no output
					else
					{
						//notify the current gate it has got an extra input
						module->gates[curGate].inputSize++;

						//notifiy the connected gate it has to output to this one
						for(k = 0; k <= curGate; k++)
						{
							if(_destArray[k] == i)
							{
								module->gates[k].output[ module->gates[k].outputSize++ ] = curGate;
								break;
							}
						}
					}
				}

        		g_scanner_get_next_token(scanner);
			}
		}
		else
		{
			logs_build_update_status(logHandle, "\nError: getArgument failed\n");
			break;
		}
	  //found comma no right paren so go on searching
	} while(scanner->token == ',' && g_scanner_get_next_token(scanner));

	return(1);
}

guint compile(GScanner *scanner, Module *moduleArray)
{
    //the first item of this array is the entry
    int moduleIndex, lastModuleIndex;
    moduleIndex = 1;
    //mode is for get argument function 0=input 1=operand 2=destination
    int i, mode;

    //loop until the end of file
    while(TRUE)
    {
        g_scanner_get_next_token(scanner);

        //is it a module
        if(scanner->token == G_TOKEN_IDENTIFIER && !g_strcmp0(scanner->value.v_identifier, "module"))
        {
        	g_scanner_get_next_token(scanner);
			//get the id of this module
			int id = g_quark_from_string(scanner->value.v_identifier);
			//store in buffer so it is easy to find for compiler
			_moduleIdArray[_moduleSize++] = id;

            logs_build_update_status(logHandle, g_strdup_printf("\nModule[%d]", id));

      		//is it the entry
            if(scanner->token == G_TOKEN_IDENTIFIER && !g_strcmp0(scanner->value.v_identifier, "entry"))
            {
                lastModuleIndex = moduleIndex;
                moduleIndex = 0;
            }
            moduleArray[moduleIndex].ID = id;

            //scan for input
            if(g_scanner_get_next_token(scanner) == G_TOKEN_LEFT_PAREN)
            {
            	logs_build_update_status(logHandle, "\n\tInput:");
				g_scanner_get_next_token(scanner);
				//mode 0 for input
				getArgument(scanner, &moduleArray[moduleIndex], 0);
           		if(scanner->token == G_TOKEN_RIGHT_PAREN)
           		{
           			g_scanner_get_next_token(scanner);
           		}
			}

			//scan for instructions
			if(scanner->token == G_TOKEN_LEFT_CURLY)
			{
				//FIXME I AM A VERY VERY VERY UGLY SOLUTION ( BUT I WORK)
				moduleArray[moduleIndex].gateSize = -1;

				mode = 1;
				g_scanner_get_next_token(scanner);
				do
				{
					//for destination
					getArgument(scanner, &moduleArray[moduleIndex], mode);
					mode = 1;

					if(scanner->token == G_TOKEN_EQUAL_SIGN)
					{
						//mode 2 for operand
						moduleArray[moduleIndex].gateSize++;
						mode = 2;
						logs_build_update_status(logHandle, g_strdup_printf("\n\tGate[%d]: ", moduleArray[moduleIndex].gateSize));
					}
					g_scanner_get_next_token(scanner);
                } while(scanner->token != G_TOKEN_RIGHT_CURLY);

                //I AM ALSO PART OF THE PROBLEM
                moduleArray[moduleIndex].gateSize++;
			}

			//clean data
			for(i = 0; i < moduleArray[moduleIndex].inputSize; i++)
			{
				moduleArray[moduleIndex].input[i] = 0;
			}

			moduleIndex++;
        }

        g_scanner_peek_next_token(scanner);
        //make sure we exit the loop before some error ocures
        if(scanner->next_token == G_TOKEN_EOF)
        {
            logs_build_update_status(logHandle, g_strdup_printf("\nEnd of file reached, line:%u, column:%u\n", scanner->next_line, scanner->next_position));
            return(1);
        }
    }
    return (1);
}

int compileEntry(Module *moduleArray, char *fileName)
{
    gint fileDescriptor;
    GScanner *scanner;

    scanner = g_scanner_new (NULL);
    //set config for scanner
    scanner->config->cpair_comment_single = "//\n";
    scanner->config->scan_identifier_1char = 1;
    scanner->config->symbol_2_token = 1;
    scanner->config->store_int64 = 0;

    if(fileName)
    	fileDescriptor = g_open(fileName, 0);
    else
    	fileDescriptor = g_open("/home/elbert/Cahd/Examples/simpleTest.hd", 0);

    if(fileDescriptor == -1)
    {
        logs_build_update_status(logHandle, "ERROR: Couldnt open file.\n Compilation terminated.\n");
        return(-1);
    }

    logs_build_update_status(logHandle, "Compilation started\n");

    g_scanner_input_file(scanner ,fileDescriptor);

    compile(scanner, moduleArray);

    //clean up before we return
    g_scanner_destroy (scanner);
    g_close(fileDescriptor, NULL);

    return 0;
}
