#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
struct node
{
	int ntt;
	int cc;
};

void main()
{
	int nl;
	printf("How many nodes in the network\n"); //inputting the number of nodes from user
	scanf("%d", &nl);
	struct node n[nl]; // initialising an array of struct
	int ct = 0;
	int i, j, a, k, p = 0, q;
	int nts = 0;
	int r, t, x, num, wait = 0;
	srand(time(NULL));
	for (i = 0, num = 0; i<nl; i++)
	{
		n[i].ntt = 1;//initialising initial values of next time to send variable

		n[i].cc = 0;
	}
	
	do
	{   //detect collision
	    ct+=1; // current time incremented 
		srand(time(NULL));
		for (k = 0; k<nl; k++)
		{

			if (ct == n[k].ntt || n[k].ntt == n[k + 1].ntt)//checking if any 2 have same next time or matching with current time
			{

				n[k].cc += 1;
				int h = rand();
				a = h % 2;          //computing a value which determines the next state(coin toss result)
				p += n[k].cc;
				//printf("a value is %d\n", a);
				x = (2 ^ p) - 1;
				//computing the r value which is the factor by which next time to send variable is incremented
				if (x >= 2)
				{
					q = rand();
					//printf("x is %d\n q is %d\n", x, q);
					r = q%x;
					//printf("r value is %d\n", r);
				}
				//to avoid higher r value because of division by 1
				else
				{
					r = rand() % 2;
					//printf("r value(less than 2) is %d\n", r);
				}
				if (a == 0)		//increment next time by 1 cycle
				{
					n[k].ntt += r;
					ct++;
					//printf("Exec 1st\n ");

				}
				else if (a == 1) //increment to next 2 cycles
				{
					n[k].ntt += r + 1;
					ct++;
					//printf("Exec 2nd\n");

				}
				else{
					printf("Errorrrrrrr\n");
				}
				nts += n[k].ntt;
				//printf("Next time to send is %d\n", nts);
				//printf("ct now is %d\n", ct);
			}
			else
				wait += 1;
		    		}
		
		if (ct != nts)	//ct still not equal to nts after traversing through all nodes
		{
			ct++;
			//printf("Incremented CT is %d\n", ct);
		}

	} while (ct != nts);
	//printf("Next time to Send is %d\n", nts);
	//printf("%d th time of evaluation",c);
	
	//printf("total wait time before collision is %d\n", wait);
	
	printf("total time taken is %d\n", ct);
	
	/*for(i=0;i<30;i++)
	{
	    printf("%d\n",result[i]);
	    }*/
}
