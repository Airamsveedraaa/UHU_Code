<!-- R Commander Markdown Template -->

PRACTICA 8,REGRESIONES (SOLO LINEALES, NO DIO TIEMPO A MAS)
=======================

### Your Name

### 2025-06-03








```r
> load("C:/Users/Airam/Downloads/RCars_EN (2).RData")
```
The regression model we have to study is:
accel = ?0 + ?1 · cylindr + ?2 · HP + ?3 · weight + ?4 · engine + ?

a) Find and explain the coefficient of determination.

accel=17.9285204-0.2567606cylindr-0.0869459HP+0.0091757Weight-0.0003232engine the numbers are the coefficientes for B0 B1 B2 B3 B4 in that order


b) Is there a linear relationship between the regressor variables and the dependent
one? What conclusion is obtained for a level of significance ? = 0.05?

only the hp and the weight have a relationship between the dependent variable and the regressors
this is, we can take 0 on B1 and B2, and our model will be like:
accel=B3*weight+B4*engine+E

c) Can any of the model coefficients be assumed null, for a significance of 0.05?
B1 and B2

d) Express the model after obtaining estimates of the coefficient. Find 95 % confidence
intervals for the model coefficients.

accel=-0.2567606*0-0.0003232*0-0.0869459*B3+0.0091757*B4


```r
> Model_1 <- lm(accel~cylind+engine+HP+weight, data=RCars_en)
> summary(Model_1)
```

```

Call:
lm(formula = accel ~ cylind + engine + HP + weight, data = RCars_en)

Residuals:
    Min      1Q  Median      3Q     Max 
-4.3517 -1.0039 -0.2005  0.9210  6.6656 

Coefficients:
              Estimate Std. Error t value Pr(>|t|)    
(Intercept) 17.9285204  0.6162686  29.092   <2e-16 ***
cylind      -0.2567606  0.1631586  -1.574    0.116    
engine      -0.0003232  0.0002221  -1.455    0.146    
HP          -0.0869459  0.0051395 -16.917   <2e-16 ***
weight       0.0091757  0.0008549  10.734   <2e-16 ***
---
Signif. codes:  0 '***' 0.001 '**' 0.01 '*' 0.05 '.' 0.1 ' ' 1

Residual standard error: 1.695 on 394 degrees of freedom
  (7 observations deleted due to missingness)
Multiple R-squared:  0.6382,	Adjusted R-squared:  0.6345 
F-statistic: 173.8 on 4 and 394 DF,  p-value: < 2.2e-16
```


```r
> library(MASS, pos=25)
```



```r
> Confint(Model_1, level=0.95)
```

```
                 Estimate         2.5 %        97.5 %
(Intercept) 17.9285203912 16.7169343005 19.1401064820
cylind      -0.2567605998 -0.5775308800  0.0640096803
engine      -0.0003232064 -0.0007598773  0.0001134645
HP          -0.0869458670 -0.0970500494 -0.0768416847
weight       0.0091756876  0.0074950265  0.0108563486
```


```r
> options(encoding="utf-8")
```



