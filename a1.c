#include <stdio.h>
#define J 2

int main ()
{
	int count_l2, repetj, linha, linha2, count;
	
	scanf("%d", &linha);
	
	for ( count = 0; count < linha; count++ )
	{
		if (count > 0)
			printf("\n");
		scanf("%d", &linha2);
		if ( linha2 == 1 )
			printf("#\n");
		else
		{
			for( count_l2 = 0; count_l2 < linha2-1; count_l2++ )
			{
				printf("#");
			}
	
			printf("#\n");
		
			for ( repetj = 0; repetj < linha2-J; repetj++ )
			{
				printf("#");
				for ( count_l2 = 0; count_l2 < linha2-J; count_l2++ )
					printf("J");
				printf("#\n");
			}
		
			for( count_l2 = 0; count_l2 < linha2-1; count_l2++ )
			{
				printf("#");
			}
		
			printf("#\n");
		}

	}
	
	return 0;
}
	
