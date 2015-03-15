#ifndef CS451PROJECT_H_INCLUDED
#define CS451PROJECT_H_INCLUDED


        char *Ending(int a, int b)
        {
                char *suffix = "";
                int th[] = {0,4,5,6,7,8,9};
                int ct;
                for (ct = 0; ct < 7; ++ct) /* This is a loop to see if last digit is equal to any element within the list */
                {
                        if (a == th[ct]) /* if last digit of input number within the list */
                                suffix = "th";
                }

                if (a == 1) /* if last digit of input number is 1 */
                {
                        if (b == 11)
                                suffix = "th";
                        else
                                suffix = "st";
                }

                else if (a == 2) /* if last digit of input number is 2 */
                {
                        if (b == 12) /*   */
                                suffix = "th";
                        else
                                suffix = "nd";
                }

                else if (a == 3) /* if last digit of fib number is 3 */
                        suffix = "rd";


                return suffix;
        }



        int validate(int num)
        {

                char input[256]; // arbitrary size buffer
                char* cp, badc; // badc is for detecting extraneous chars in the input
                int n;

                while (num < 0)
                {
                        cp = fgets(input, sizeof(input), stdin);
                        if (cp == input)
                        {
                                n = sscanf(input, "%d %c", &num, &badc);
                                if (n != 1) // if badc captured an extraneous char
                                {
                                        printf("Error! Please enter a number: ");
                                        num = -1;
                                }
                                else if (num < 0)
                                        printf("Error! Please enter a POSITIVE number: ");
                        }
                }

                return num;
        }



        unsigned long long int fib(int m)
        {
                if (m==0)
                   return 0;

                if (m == 1)
                   return 1;

                return fib(m-2) + fib(m-1);
        }



        void PressEnterToContinue(void)
        {
           printf(" Press ENTER to continue: ");
           while (1)
           {
                char c = getchar();
                if (c=='\n' || c==EOF)
                        break;
           }

#endif
