#include<stdio.h>
#include<string.h>
#include<math.h>

/*
    ->STATUS: Under Development!
        
        To do:
            1 - Additional granted
            2 - Create a description
*/

/*
    *Remember: ALL THESE VALUES ARE BASED ON BRAZILIAN LEGISLATION (2024)

    INSS = Instituto Nacional do Seguro Social | Brazilian Social Security Institute
    IRRF = Imposto de Renda Retido na Fonte | Withholding Income Tax
    FGTS = Fundo de Garantia do Tempo de Serviço | Service Time Guarantee
*/

float salary = 0;

float fgtsTax = 0.08;

float inssTable[5][4] = {
        {0, 1412.00, 7.5, 0},
        {1412.01, 2666.68, 9, 21.18},
        {2666.69, 4000.03, 12, 101.18},
        {4000.04, 7786.02, 14, 181.18},
        {7786.02, 0, 908.86, 0}
    };

float irrfTable[5][4] = {
        {0, 2112.00, 0, 0},
        {2112.01, 2826.65, 7.5, 158.40},
        {2826.66, 3751.05, 15, 370.40},
        {3751.06, 4664.68, 22.5, 651.73},
        {4664.68, INFINITY, 27.5, 884.96}
    };

float deductionDep = 189.59;


float taxBusinessDay = 0.5;
float taxSundayAndHolidays = 1;


float reducedNightHour = 1.142857;
float additionalNight = 20;


float calculateINSS(){

    float contributionValue = 0;

    printf("\n-----------------------------------------------\nINSS:");
    for(int i = 0; i<5;i++){
        if(salary > inssTable[4][0]){
            printf("\n    Max descount: %.2f",inssTable[4][2]);
            contributionValue = inssTable[4][2];
            break;
        }
        if(inssTable[i][0]<=salary && salary <= inssTable[i][1]){
            printf("\n\n    Aliquot: %.0f%%\n    Portion to be deducted: R$ %.2f\n",inssTable[i][2],inssTable[i][3]);
            contributionValue = (salary * (inssTable[i][2]/100));
            printf("\n      %.2f * %.0f%% = %.2f",salary, inssTable[i][2],contributionValue);
            printf("\n      %.2f - %.2f = ",contributionValue,inssTable[i][3]);
            contributionValue = contributionValue - inssTable[i][3];
            printf("%.2f",contributionValue);
            break;
        }
    }    
    printf("\n\n-----------------------------------------------");
    return contributionValue;
}


//WAC = WITH ANOTHER COMPANY
float calculateINSSWAC(float contributionValue, float contributionAC){
    
    float totalContribution = 0;

    printf("\nINSS with 2 companies: ");
    printf("\n\n      %.2f + %.2f = ",contributionValue, contributionAC);
    totalContribution = contributionValue + contributionAC;
    printf("%.2f",totalContribution);
    if(totalContribution > inssTable[4][2]){
        printf("\n\n      %.2f - %.2f = ",totalContribution, inssTable[4][2]);
        totalContribution = totalContribution - inssTable[4][2];
        printf("%.2f",totalContribution);
        printf("\n\n      %.2f - %.2f = ",contributionValue, totalContribution);
        contributionValue = contributionValue - totalContribution;
        printf("%.2f",contributionValue);
    }
    printf("\n\n-----------------------------------------------");
    return(contributionValue);
}


float calculateIRRF(float salaryWithoutINSS, int numberOfDependents){

    float contributionValue;
    contributionValue = 0;

    printf("\n-----------------------------------------------\nIRRF:");
    for(int i=0; i<5; i++){
        if(salaryWithoutINSS < irrfTable[0][1]){
            printf("\n The salary is in the exemption range!");
            break;
        }
        if(irrfTable[i][0]<= salaryWithoutINSS && salaryWithoutINSS <= irrfTable[i][1]){
            printf("\n\n    Aliquot: %.1f%%\n    Portion to be deducted: R$ %.2f\n",irrfTable[i][2],irrfTable[i][3]);
            contributionValue = (salaryWithoutINSS * (irrfTable[i][2]/100));
            printf("\n      %.2f * %.1f%% = %.2f",salaryWithoutINSS, irrfTable[i][2],contributionValue);
            printf("\n      %.2f - %.2f = ",contributionValue,irrfTable[i][3]);
            contributionValue = contributionValue - irrfTable[i][3];
            printf("%.2f",contributionValue);
            if(numberOfDependents != 0){
                printf("\n\n      Deduction for dependent: ");
                printf("%.2f - (%.2f * %i) = ",contributionValue, deductionDep, numberOfDependents);
                contributionValue = contributionValue - (deductionDep * numberOfDependents);
                printf("%.2f",contributionValue);
                if(contributionValue <= 0){
                    printf("\n      The contribution value is 0!");
                    contributionValue = 0;
                }
            }    
            break;
        }
    }
    printf("\n-----------------------------------------------");
    return(contributionValue);
}


float calculateEmployerSocialSecurityContribution(int risk, float taxPercentage){
    float contributionValue;

    switch (risk){
        case 1:
            taxPercentage = 26.8;
            break;
        case 2:
            taxPercentage = 27.8;
            break;
        case 3:
            taxPercentage = 28.8;
            break;
        case 4:
            taxPercentage = taxPercentage;
            break;  
        default:
            printf("\n *** Invalid option! ***\n\nPress 'enter' to continue!\n");
            getchar();
            getchar();
            return 0; 
    }

    contributionValue = salary * (taxPercentage/100);
    printf("\n-----------------------------------------------");
    printf("\nEmployer Social Security Contribution:");
    printf("\n\n      %.2f * %.1f%% = %.2f",salary, taxPercentage, contributionValue);
    printf("\n\n-----------------------------------------------");
    return (contributionValue);
}


float calculateLaborBenefits(float laborBenefits[3]){
    
    printf("\n-----------------------------------------------\nLabor Benefits:\n");
    //13º salary
    laborBenefits[0] = (salary/12);
    printf("\n      %.2f / 12 = %.2f",salary,laborBenefits[0]);
    //Vacation
    laborBenefits[1] = (salary/12);
    printf("\n      %.2f / 12 = %.2f",salary,laborBenefits[1]);
    //1/3 Vacation
    laborBenefits[2] = (laborBenefits[1]/3);
    printf("\n      %.2f / 3 = %.2f",laborBenefits[1],laborBenefits[2]);
    //Total
    laborBenefits[3] = laborBenefits[0]+laborBenefits[1]+laborBenefits[2];
    printf("\n\n-----------------------------------------------");
}


float calculateOvertime(float overtimeAndBonuses[], float hours, float hoursOnBusinessDay, float hoursOnSundaysAndHolidays){
    
    printf("\n-----------------------------------------------\nOvertime:");
    //Hourly rate
    overtimeAndBonuses[0] = (salary/hours);
    printf("\n\n     %.2f / %.2f = %.2f",salary,hours,overtimeAndBonuses[0]);
    //Overtime on business days
    overtimeAndBonuses[1] = ((hoursOnBusinessDay * overtimeAndBonuses[0]) * taxBusinessDay);
    printf("\n\n     ((%.2f * %.2f) * %.2f) = %.2f",hoursOnBusinessDay, overtimeAndBonuses[0], taxBusinessDay, overtimeAndBonuses[1]);    
    //Overtime on Sundays and holidays
    overtimeAndBonuses[2] = ((hoursOnSundaysAndHolidays * overtimeAndBonuses[0]) * taxSundayAndHolidays);
    printf("\n\n     ((%.2f * %.2f) * %.2f) = %.2f",hoursOnSundaysAndHolidays, overtimeAndBonuses[0], taxSundayAndHolidays, overtimeAndBonuses[2]);
    //Total overtime
    overtimeAndBonuses[3] = (overtimeAndBonuses[1] + overtimeAndBonuses[2]);
    printf("\n\n     %.2f + %.2f = %.2f",overtimeAndBonuses[1], overtimeAndBonuses[2], overtimeAndBonuses[3]);
    printf("\n\n-----------------------------------------------");

}

float calculateNightDifferentialPay(float overtimeAndBonuses[], float hours, float hoursAtNight){
    
    printf("\n-----------------------------------------------\nNight Differential Pay:");
    //Hourly rate
    overtimeAndBonuses[0] = (salary/hours);
    printf("\n\n     %.2f / %.2f = %.2f",salary,hours,overtimeAndBonuses[0]);
    //Total night hours worked
    overtimeAndBonuses[1] = (hoursAtNight * reducedNightHour);
    printf("\n\n     %.2f * %.2f = %.2f",hoursAtNight, reducedNightHour, overtimeAndBonuses[1]);
    //Night differential pay
    overtimeAndBonuses[2] = (overtimeAndBonuses[0] * (additionalNight/100));
    printf("\n\n     %.2f * %.2f%% = %.2f",overtimeAndBonuses[0], additionalNight, overtimeAndBonuses[2]);
    printf("\n\n     %.2f * %.2f",overtimeAndBonuses[1],overtimeAndBonuses[2]);
    overtimeAndBonuses[2] = overtimeAndBonuses[1] * overtimeAndBonuses[2];
    printf("= %.2f", overtimeAndBonuses[2]);
    //Total night differential pay
    overtimeAndBonuses[3] = salary + overtimeAndBonuses[2];
    printf("\n\n     %.2f + %.2f = %.2f",salary, overtimeAndBonuses[2], overtimeAndBonuses[3]);
    printf("\n\n-----------------------------------------------");
}


int main(){

    int i, option, risk, numberOfDependents;
    float contributionValue[3] = {0, 0, 0}, overtimeAndBonuses[4] = {0, 0, 0, 0};   
    /*
        contributionValue[0] = FTGS
        contributionValue[1] = INSS
        contributionValue[2] = IRRF
    */
    float laborBenefits[4], contributionAC, taxPercentage, inssEmploye, hours, hoursOnBusinessDay, hoursOnSundaysAndHolidays, hoursAtNight;
    char hasContribute[1];
    
    i = contributionAC = taxPercentage = inssEmploye = 0;

    while(i!=1){
        printf("\n******************************");
        printf("\n\n 1 - FGTS | INSS | IRRF\n 2 - INSS Employe\n 3 - Labor benefits -> 13º salary | vacation | 1/3 vacation\n 4 - Overtime and bonuses\n 5 - Exit\n\n");
        printf(" ->Select your option: ");
        scanf("%i",&option);

        switch(option){
            case 1:
                printf("\n******************************");
                printf("\n --- FGTS | INSS | IRRF ---");

                printf("\n\n Tip: Salary is composed of: salary + commission + gratification + tips + labor benefits");
                printf("\n\n\n-> Enter the salary: ");
                scanf("%f",&salary);

                //Calculating the FGTS
                contributionValue[0] = (salary * fgtsTax);

                //Calculating the INSS
                printf("\n-> Did the employee contribute to another company (y/n)? ");
                scanf(" %c",&hasContribute[0]);
            
                if(hasContribute[0] == 'y'){
                    printf("\n      ->Enter the contribution of another company: ");
                    scanf("%f",&contributionAC);

                    if(contributionAC<inssTable[4][2]){
                        contributionValue[1] = calculateINSS(salary);
                        contributionValue[1] = calculateINSSWAC(contributionValue[1], contributionAC);
                    }else{
                        printf("\n      *You don't need to pay the INSS tax, because the contribution of another company is equal to or higher than the maximum tax!\n\n");
                        contributionValue[1] = 0;
                    }
                }else{
                    contributionValue[1] = calculateINSS(salary);
                }
                
                //Calculating the IRRF
                printf("\n\n-> Enter the number of dependents: ");
                scanf("%i",&numberOfDependents);
                contributionValue[2] = calculateIRRF((salary - contributionValue[1]),numberOfDependents);

                printf("\n\nResults:\n    -> The contributions values are: \n        FGTS: $%.2f\n        INSS: $%.2f\n        IRRF: $%.2f\n\n",contributionValue[0],contributionValue[1],contributionValue[2]);
                break;
            
            case 2:
                printf("******************************");
                printf("\n Employer Social Security Contribution\n\n");
                printf("\n\n To remember:\n     Salary is composed of: salary + commission + gratification + tips + labor benefits");
                
                printf("\n\n -> Enter the payroll amount: ");
                scanf("%f",&salary);

                contributionValue[0] = (salary * fgtsTax);
                
                printf("\n -> Set the Occupational Accident Risk:\n   1 - Low(26.8%%)\n   2 - Medium(27.8%%)\n   3 - High(28.8%%)\n   4 - Set your percentage\n  Option: ");
                scanf("%i",&risk);

                if(risk == 4){
                    do{
                        printf("\n -> Enter the percentage: ");
                        scanf("%f",&taxPercentage);
                        if(taxPercentage>100){
                            printf("\n *You can't set a percentage higher than 100%%\n\n");
                        }
                    }while(taxPercentage>100);
                }

                inssEmploye = calculateEmployerSocialSecurityContribution(risk,taxPercentage);

                if(inssEmploye != 0){
                    printf("\n\nResults:\n     Employer Social Security Contribution value is: $%.2f\n     FGTS: $%.2f\n",inssEmploye,contributionValue[0]);
                }
                break;

            case 3:
                printf("******************************");
                printf("\n\n 13º salary | vacation | 1/3 vacation");
                printf("\n\n -> Enter the salary: ");
                scanf("%f",&salary);

                calculateLaborBenefits(laborBenefits);
                printf("\nResults:\n     13º salary: $%.2f\n     vacation: $%.2f\n     1/3 vacation: $%.2f\n\n  Total: $%.2f\n",laborBenefits[0], laborBenefits[1], laborBenefits[2], laborBenefits[3]);
                break;

            case 4:
                printf("******************************");
                printf("\n\n Overtime and bonuses");

                printf("\n\n -> Enter the salary: ");
                scanf("%f",&salary);
                printf("\n\n -> How many hours per month are there in a regular work schedule? ");
                scanf("%f",&hours);

                printf("\n\n 1 - Value of the hour worked\n 2 - Overtime\n 3 - Night differential pay\n");
                printf(" -> Select your option: ");
                scanf("%i",&option);
                switch(option){
                    case 1:
                        salary = (salary/hours);
                        printf("\n-----------------------------------------------");
                        printf("\nResults:\n     The value of the hour worked is: $%.2f\n",salary);
                        break;

                    case 2:
                        printf("\n -> How many overtimes hours were worked on business day (50%%)? ");
                        scanf("%f",&hoursOnBusinessDay);
                        printf("\n -> How many overtimes hours were worked on sundays and holidays (100%%)? ");
                        scanf("%f",&hoursOnSundaysAndHolidays);
                        
                        calculateOvertime(overtimeAndBonuses, hours, hoursOnBusinessDay, hoursOnSundaysAndHolidays);
                        printf("\nResults:\n     Hourly rate: $%.2f\n     Business days: $%.2f\n     Sundays and Holidays: $%.2f \n     Total: $%.2f\n",overtimeAndBonuses[0],overtimeAndBonuses[1],overtimeAndBonuses[2],overtimeAndBonuses[3]);
                        break;
                
                    case 3:
                        printf("\n -> How many hours were worked during the night? ");
                        scanf("%f",&hoursAtNight);

                        calculateNightDifferentialPay(overtimeAndBonuses, hours, hoursAtNight);
                        printf("\nResults:\n     Hourly rate: $%.2f\n     Total night hours worked: %.2f Hours\n     Night differential pay: $%.2f \n     Total: $%.2f\n",overtimeAndBonuses[0],overtimeAndBonuses[1],overtimeAndBonuses[2],overtimeAndBonuses[3]);
                        break;

                    default:
                        printf("\n *** Invalid option! ***\n\nPress 'enter' to continue!\n");
                        getchar();
                        getchar();
                        break;
                }
                break;

            case 5:
                return 0;
            
            default:
                printf("\n *** Invalid option! ***\n\nPress 'enter' to continue!\n");
                getchar();
                getchar();
                break;
        }
    }
}
