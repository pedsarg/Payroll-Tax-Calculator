#include<stdio.h>
#include<string.h>

/*
    To do:
        1 - Deduction for dependent (INSS)
        2 - Additional granted
        3 - Review the code
*/
//Payroll Tax Calculator


float tax5 = 908.86;

float calculateINSS(float salary){

    float contributionValue = 0;
    float tax1[2] = {0.075, 0.00};    
    float tax2[2] = {0.09, 21.18};    
    float tax3[2] = {0.12, 101.18};   
    float tax4[2] = {0.14, 181.18};

    printf("\n-----------------------------------------------");
    if(salary <= 1412.00){
        printf("\n Aliquot: %.3f%\n Portion to be deducted: R$ %.2f\n", tax1[0],tax1[1]);
        contributionValue = (salary * tax1[0]); 
        printf("\n\n    %2.f * %.3f = %.2f",salary,tax1[0],contributionValue);
    }
    if(1412.01 <= salary && salary <= 2666.68){
        printf("\n Aliquot: %.2f%\n Portion to be deducted: R$ %.2f\n",tax2[0],tax2[1]);
        contributionValue = (salary * tax2[0]);
        printf("\n      %.2f * %.2f = %.2f",salary, tax2[0],contributionValue);
        printf("\n      %.2f - %.2f = ",contributionValue,tax2[1]);
        contributionValue = contributionValue - tax2[1];
        printf("%.2f",contributionValue);
    }
    if(2666.69 <= salary && salary <= 4000.03){
        printf("\n Aliquot: %.2f%\n Portion to be deducted: R$ %.2f\n",tax3[0],tax3[1]);
        contributionValue = (salary * tax3[0]);
        printf("\n      %.2f * %.2f = %.2f",salary, tax3[0],contributionValue);
        printf("\n      %.2f - %.2f = ",contributionValue,tax3[1]);
        contributionValue = contributionValue - tax3[1];
        printf("%.2f",contributionValue);
    }
    if(4000.04 <= salary && salary <= 7786.02){
        printf("\n Aliquot: %.2f%\n Portion to be deducted: R$ %.2f\n",tax4[0],tax4[1]);
        contributionValue = (salary * tax4[0]);
        printf("\n      %.2f * %.2f = %.2f",salary, tax4[0],contributionValue);
        printf("\n      %.2f - %.2f = ",contributionValue,tax4[1]);
        contributionValue = contributionValue - tax4[1];
        printf("%.2f",contributionValue);
    }
    if(salary > 7786.02){
        printf("\n Max descount: %.2f",tax5);
        contributionValue = tax5;
    }
    printf("\n-----------------------------------------------");

    return(contributionValue);
}

//WAC = WITH ANOTHER COMPANY
float calculateINSSWAC(float contributionValue, float contributionAC){
    float totalContribution = 0;

    printf("\n-----------------------------------------------");
    
    printf("\n      %.2f + %.2f = ",contributionValue, contributionAC);
    totalContribution = contributionValue + contributionAC;
    printf("%.2f",totalContribution);
    printf("\n\n    %.2f - %.2f = ",totalContribution, tax5);
    totalContribution = totalContribution - tax5;
    printf("%.2f",totalContribution);
    printf("\n\n    %.2f - %.2f = ",contributionValue, totalContribution);
    contributionValue = contributionValue - totalContribution;
    printf("%.2f",contributionValue);

    
    printf("\n-----------------------------------------------");

    return(contributionValue);
}


float calculateIRRF(float salary, int dependents){

    float contributionValue = 0;
    float IRRF1[2] = {0.0, 0.0};    
    float IRRF2[2] = {0.075, 158,40};    
    float IRRF3[2] = {0.15, 370.40};   
    float IRRF4[2] = {0.225, 651.73};
    float IRRF5[2] = {0.275 , 884.96};

    printf("\n-----------------------------------------------");

    if(salary <= 2112.00){
        printf("\n Aliquot: %.3f%\n Portion to be deducted: R$ %.2f\n", IRRF1[0],IRRF1[1]);
        contributionValue = (salary * IRRF1[0]); 
        printf("\n\n    %2.f * %.3f = %.2f",salary,IRRF1[0],contributionValue);
    }
    if(2112.01 <= salary && salary <= 2826.65){
        printf("\n Aliquot: %.2f%\n Portion to be deducted: R$ %.2f\n",IRRF2[0],IRRF2[1]);
        contributionValue = (salary * IRRF2[0]);
        printf("\n      %.2f * %.2f = %.2f",salary, IRRF2[0],contributionValue);
        printf("\n      %.2f - %.2f = ",contributionValue,IRRF2[1]);
        contributionValue = contributionValue - IRRF2[1];
        printf("%.2f",contributionValue);
    }
    if(2826.66 <= salary && salary <= 3751.05){
        printf("\n Aliquot: %.2f%\n Portion to be deducted: R$ %.2f\n",IRRF3[0],IRRF3[1]);
        contributionValue = (salary * IRRF3[0]);
        printf("\n      %.2f * %.2f = %.2f",salary, IRRF3[0],contributionValue);
        printf("\n      %.2f - %.2f = ",contributionValue,IRRF3[1]);
        contributionValue = contributionValue - IRRF3[1];
        printf("%.2f",contributionValue);
    }
    if(3751.06 <= salary && salary <= 4664.68){
        printf("\n Aliquot: %.2f%\n Portion to be deducted: R$ %.2f\n",IRRF4[0],IRRF4[1]);
        contributionValue = (salary * IRRF4[0]);
        printf("\n      %.2f * %.2f = %.2f",salary, IRRF4[0],contributionValue);
        printf("\n      %.2f - %.2f = ",contributionValue,IRRF4[1]);
        contributionValue = contributionValue - IRRF4[1];
        printf("%.2f",contributionValue);
    }
    if(salary > 4664.68){
        printf("\n Aliquot: %.2f%\n Portion to be deducted: R$ %.2f\n",IRRF5[0],IRRF5[1]);
        contributionValue = (salary * IRRF5[0]);
        printf("\n      %.2f * %.2f = %.2f",salary, IRRF5[0],contributionValue);
        printf("\n      %.2f - %.2f = ",contributionValue,IRRF5[1]);
        contributionValue = contributionValue - IRRF5[1];
        printf("%.2f",contributionValue);
    }
    printf("\n-----------------------------------------------\n");

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
    return contributionValue;
    
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
        printf("1 - FGTS | INSS | IRRF\n2 - INSS Employe\n3 - 13º salary | vacation | 1/3 vacation\n4 - Exit\n\n");
        printf("Select your option: ");
        scanf("%i",&option);

        switch(option){
            case 1:
                printf("\n\n --- FGTS | INSS | IRRF ---\n");

                printf("\n\n To remember:\n     Salary is composed of: salary + commission + gratification + tips + labor benefits");
                printf("\n\n-> Enter the salary: ");
                scanf("%f",&salary);

                //Calculating the FGTS
                contributionValue[0] = (salary * 0.08);

                //Calculating the INSS
                printf("\n\n-> Did the employee contribute to another company (y/n)? ");
                scanf(" %c",&hascontribute[0]);
            
                if(hascontribute[0] == 'y'){
                    printf("\n Enter the contribution of another company: ");
                    scanf("%f",&contributionAC);

                    if(contributionAC<tax5){
                        contributionValue[1] = calculateINSS(salary);
                        contributionValue[1] = calculateINSSWAC(contributionValue[1], contributionAC);
                    }else{
                        printf("\n\n ->You don't need to pay the INSS tax because the other contribution is equal to or higher than the maximum tax!\n\n");
                        contributionValue[1] = 0;
                        break;
                    }
                }else{
                    contributionValue[1] = calculateINSS(salary);
                }
                
                //Calculating the IRRF
                printf("\n -> Enter the number of dependents: ");
                scanf("%i",&dependents);
                contributionValue[2] = calculateIRRF((salary - contributionValue[1]),dependents);

                printf("\n -> The contributions values are: \n      FGTS: %.2f\n        INSS: %.2f\n        IRRF: %.2f\n\n",contributionValue[0],contributionValue[1],contributionValue[2]);
                break;
            
            case 2:

                printf("\n Employer Social Security Contribution\n\n");
                printf("\n\n To remember:\n     Salary is composed of: salary + commission + gratification + tips + labor benefits");
                
                printf("\n\n-> Enter the salary: ");
                scanf("%f",&salary);
                
                printf("\n -> Set the Occupational Accident Risk:\n   1 - Low(26.8%)\n   2 - Medium(27.8%)\n   3 - High(28.8%)\n   4 - Set your percentage");
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

                printf("\n\n Employer Social Security Contribution value is: %.2f",inssEmploye);


                break;
            case 3:
            printf("\n\n -> 13º salary | vacation | 1/3 vacation\n\n");
                printf("\n\n-> Enter the salary: ");
                scanf("%f",&salary);

                calculateLaborBenefits(salary, laborBenefits);

                if(laborBenefits == NULL){
                    printf("\n\n ***  Error: Memory allocation failed! ***\n\n");
                    return 0;
                }
                printf("\n  13º salary: %.2f\n  vacation: %.2f\n  1/3 vacation: %.2f\n\n  Total: %.2f\n\n",laborBenefits[0], laborBenefits[1], laborBenefits[2], laborBenefits[3]);
                
                break;

            case 4:
                return 0;
        }
    }
}