#include<stdio.h>
#include<string.h>

/*

STATUS: Under Development!
    To do:
        1 - Deduction for dependent (INSS)
        2 - Additional granted
        3 - Review the code
*/
//Payroll Tax Calculator


float tax5 = 908.86;

float calculateINSS(float salary){

    float contributionValue = 0;

    float inssTable[5][4] = {
        {0, 1412.00, 0.075, 0},
        {1412.01, 2666.68, 0.09, 21.18},
        {2666.69, 4000.03, 0.12, 101.18},
        {4000.04, 7786.02, 0.14, 181.18},
        {7786.02, 0, 908.86, 0}
    };
    printf("\n-----------------------------------------------\nINSS:");
    
    for(int i = 0; i<5;i++){
        if(salary > inssTable[4][0]){
            printf("\n    Max descount: %.2f",inssTable[4][2]);
            contributionValue = inssTable[4][2];
            break;
        }
        if(inssTable[i][0]<=salary && salary <= inssTable[i][1]){
            printf("\n\n    Aliquot: %.2f%\n    Portion to be deducted: R$ %.2f\n",inssTable[i][2],inssTable[i][3]);
            contributionValue = (salary * inssTable[i][2]);
            printf("\n      %.2f * %.2f = %.2f",salary, inssTable[i][2],contributionValue);
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
    if(totalContribution > tax5){
        printf("\n\n      %.2f - %.2f = ",totalContribution, tax5);
        totalContribution = totalContribution - tax5;
        printf("%.2f",totalContribution);
        printf("\n\n      %.2f - %.2f = ",contributionValue, totalContribution);
        contributionValue = contributionValue - totalContribution;
        printf("%.2f",contributionValue);
    }
    printf("\n\n-----------------------------------------------");
    return(contributionValue);
}


float calculateIRRF(float salary, int dependents){

    float contributionValue,deductionDep;
    contributionValue = 0;
    
    deductionDep = 189.59;

    float irrfTable[5][4] = {
        {0, 2112.00, 0, 0},
        {2112.01, 2826.65, 0.075, 158.40},
        {2826.66, 3751.05, 0.15, 370.40},
        {3751.06, 4664.68, 0.225, 651.73},
        {4664.68, (salary+1), 0.275, 884.96}
    };

    printf("\n-----------------------------------------------\nIRRF:");
    for(int i=0; i<5; i++){
        if(salary < irrfTable[0][1]){
            printf("\n The salary is in the exemption range!");
            break;
        }
        if(irrfTable[i][0]<= salary && salary <= irrfTable[i][1]){
            printf("\n\n    Aliquot: %.3f%\n    Portion to be deducted: R$ %.2f\n",irrfTable[i][2],irrfTable[i][3]);
            contributionValue = (salary * irrfTable[i][2]);
            printf("\n      %.2f * %.3f = %.2f",salary, irrfTable[i][2],contributionValue);
            printf("\n      %.2f - %.2f = ",contributionValue,irrfTable[i][3]);
            contributionValue = contributionValue - irrfTable[i][3];
            printf("%.2f",contributionValue);
            if(dependents != 0){
                printf("\n\n      Deduction for dependent: ");
                printf("%.2f - (%.2f * %i) = ",contributionValue, deductionDep, dependents);
                contributionValue = contributionValue - (deductionDep * dependents);
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


float calculateEmployerSocialSecurityContribution(float salary, int risk, float taxPercentage){
    float contributionValue;

    switch (risk){
        case 1:
            taxPercentage = 0.268;
            break;
        case 2:
            taxPercentage = 0.278;
            break;
        case 3:
            taxPercentage = 0.288;
            break;
        case 4:
            taxPercentage = taxPercentage/100;
            break;   
    }

    contributionValue = salary * taxPercentage;
    return (contributionValue);
    
}


float calculateLaborBenefits(float salary, float laborBenefits[3]){
    //13º salary
    laborBenefits[0] = (salary/12);
    //Vacation
    laborBenefits[1] = (salary/12);
    //1/3 Vacation
    laborBenefits[2] = (laborBenefits[1]/3);
    //Total
    laborBenefits[3] = laborBenefits[0]+laborBenefits[1]+laborBenefits[2];
}



int main(){

    int i,option,risk,dependents;
    float contributionValue[3] = {0, 0, 0};   
    /*
        contributionValue[0] = FTGS
        contributionValue[1] = INSS
        contributionValue[2] = IRRF
    */
    float laborBenefits[4];
    float salary,contributionAC,taxPercentage,inssEmploye;
    char hascontribute[1];
    
    i=contributionAC=taxPercentage=inssEmploye=0;

    while(i!=1){
        printf("\n******************************");
        printf("\n\n 1 - FGTS | INSS | IRRF\n 2 - INSS Employe\n 3 - 13º salary | vacation | 1/3 vacation\n 4 - Exit\n\n");
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
                contributionValue[0] = (salary * 0.08);

                //Calculating the INSS
                printf("\n-> Did the employee contribute to another company (y/n)? ");
                scanf(" %c",&hascontribute[0]);
            
                if(hascontribute[0] == 'y'){
                    printf("\n      ->Enter the contribution of another company: ");
                    scanf("%f",&contributionAC);

                    if(contributionAC<tax5){
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
                printf("\n-> Enter the number of dependents: ");
                scanf("%i",&dependents);
                contributionValue[2] = calculateIRRF((salary - contributionValue[1]),dependents);

                printf("\nResults:\n    -> The contributions values are: \n         FGTS: %.2f\n        INSS: %.2f\n        IRRF: %.2f\n\n",contributionValue[0],contributionValue[1],contributionValue[2]);
                break;
            
            case 2:
                printf("******************************");
                printf("\n Employer Social Security Contribution\n\n");
                printf("\n\n To remember:\n     Salary is composed of: salary + commission + gratification + tips + labor benefits");
                
                printf("\n\n-> Enter the salary: ");
                scanf("%f",&salary);
                
                printf("\n -> Set the Occupational Accident Risk:\n   1 - Low(26.8%)\n   2 - Medium(27.8%)\n   3 - High(28.8%)\n   4 - Set your percentage\n  Option: ");
                scanf("%i",&risk);

                if(risk == 4){
                    printf("\n -> Enter the percentage: ");
                    scanf("%f",&taxPercentage);
                }
                if(risk != 1 && risk && 2 && risk != 3 && risk != 4){
                    printf("\n *** Invalid option! ***\n");
                    return 0;
                }

                inssEmploye = calculateEmployerSocialSecurityContribution(salary,risk,taxPercentage);

                printf("\n\n Employer Social Security Contribution value is: %.2f\n",inssEmploye);
                break;

            case 3:
                printf("******************************");
                printf("\n\n -> 13º salary | vacation | 1/3 vacation\n\n");
                printf("\n\n-> Enter the salary: ");
                scanf("%f",&salary);

                calculateLaborBenefits(salary, laborBenefits);
                printf("\n  13º salary: %.2f\n  vacation: %.2f\n  1/3 vacation: %.2f\n\n  Total: %.2f\n\n",laborBenefits[0], laborBenefits[1], laborBenefits[2], laborBenefits[3]);
                break;

            case 4:
                return 0;
        }
    }
}
