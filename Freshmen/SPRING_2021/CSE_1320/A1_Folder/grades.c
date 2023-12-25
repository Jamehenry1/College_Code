#include <stdio.h>

int main()
{
	int choice = 0;
	float grades[100];
	int time = 0;
	float gradeAvg = 0;

	while(choice != 4)
	{
		printf("\nGradebook\n");
		printf("1. Enter Grade\n");
		printf("2. View Grades\n");
		printf("3. Calculate Grade\n");
		printf("4. Exit\n");
		scanf("%d",&choice);


		switch(choice)
		{
			case 1:
				printf("Enter grade: ");
				scanf("%f",&grades[time]);
				time++;

				break;
			case 2:

				if(time == 0)
				{
				 	printf("WARNING NO GRADES HAVE BEEN ENTERED\n");

				}
				else
				{
					for(int i = 0; i < time; i++)
					{
						float g = grades[i];
						printf("Grade %d: %0.2f\n", i, g);
					}
				}

				break;
			case 3:

				for(int i = 0; i < time; i++)
				{
					gradeAvg += grades[i];

				}

				gradeAvg = gradeAvg/time;
				printf("Average: %0.2f\n", gradeAvg);

				break;

			case 4:

				break;

			default :
				printf("\nInvalid selection\n\n");


		}
	}
	return 0;
}

