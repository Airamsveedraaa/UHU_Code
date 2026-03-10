
load("C:/Users/Airam/Downloads/RCars_EN (2).RData")
Model_1 <- lm(accel~cylind+engine+HP+weight, data=RCars_en)
summary(Model_1)
library(MASS, pos=25)
Confint(Model_1, level=0.95)
options(encoding="utf-8")

