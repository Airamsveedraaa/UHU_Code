
load("C:/Users/Airam/Downloads/World95R.RData")
example1 <- subset(World95, subset=region=="OECD")
normalityTest(~b_to_d, test="shapiro.test", data=example1)
with(example1, qqPlot(b_to_d, dist="norm", id=list(method="y", n=1, 
  labels=rownames(example1))))
editDataset(example1)
normalityTest(~b_to_d, test="shapiro.test", data=example1)
802+795+752+810+783/5
802+795+752+810+783
3942/5
editDataset(Example2)
with(Example2, (t.test(tons, alternative='less', mu=800, conf.level=.95)))
with(Example4, (t.test(Time.bef, Time.aft, alternative='less', conf.level=.95, 
  paired=TRUE)))
options(encoding="utf-8")

