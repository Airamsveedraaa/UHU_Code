
local({
  .x <- 0:12
  plotDistr(.x, dbinom(.x, size=21, prob=0.25), xlab="Number of Successes", 
  ylab="Probability Mass", 
  main="Binomial Distribution:  Binomial trials=21, Probability of success=0.25", 
  discrete=TRUE)
})
local({
  .x <- 0:12
  plotDistr(.x, pbinom(.x, size=21, prob=0.25), xlab="Number of Successes",
  ylab="Cumulative Probability", 
  main="Binomial Distribution:  Binomial trials=21, Probability of success=0.25", 
  discrete=TRUE, cdf=TRUE)
})
local({
  .Table <- data.frame(Probability=dbinom(0:21, size=21, prob=0.25))
  rownames(.Table) <- 0:21 
  print(.Table)
})
qbinom(c(10), size=21, prob=0.25, lower.tail=TRUE)
pbinom(c(10), size=21, prob=0.25, lower.tail=TRUE)
pbinom(c(10), size=21, prob=0.25, lower.tail=FALSE)
local({
  .x <- 0:14
  plotDistr(.x, dpois(.x, lambda=5), xlab="x", ylab="Probability Mass", 
  main="Poisson Distribution:  Mean=5", discrete=TRUE)
})
local({
  .x <- 0:14
  plotDistr(.x, ppois(.x, lambda=5), xlab="x",ylab="Cumulative Probability", 
  main="Poisson Distribution:  Mean=5", discrete=TRUE, cdf=TRUE)
})
local({
  .Table <- data.frame(Probability=dpois(0:14, lambda=5))
  rownames(.Table) <- 0:14 
  print(.Table)
})
qpois(c(7), lambda=10, lower.tail=TRUE)
qpois(c(7), lambda=10, lower.tail=FALSE)
ppois(c(7), lambda=10, lower.tail=TRUE)
qpois(c(0.9), lambda=5, lower.tail=TRUE)
local({
  .x <- 0:26
  plotDistr(.x, dgeom(.x, prob=0.25), xlab="Number of Failures until Success", 
  ylab="Probability Mass", main="Geometric Distribution:  Probability of success=0.25", 
  discrete=TRUE)
})
local({
  .Table <- data.frame(Probability=dgeom(0:26, prob=0.25))
  rownames(.Table) <- 0:26 
  print(.Table)
})
pgeom(c(6), prob=0.25, lower.tail=TRUE)
pgeom(c(5), prob=0.25, lower.tail=TRUE)
local({
  .Table <- data.frame(Probability=dnbinom(0:40, size=3, prob=0.25))
  rownames(.Table) <- 0:40 
  print(.Table)
})
local({
  .Table <- data.frame(Probability=dhyper(0:2, m=10, n=10, k=2))
  rownames(.Table) <- 0:2 
  print(.Table)
})
local({
  .Table <- data.frame(Probability=dhyper(0:5, m=5, n=15, k=10))
  rownames(.Table) <- 0:5 
  print(.Table)
})
options(encoding="utf-8")

