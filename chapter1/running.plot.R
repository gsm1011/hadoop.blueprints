library("ggplot2")
library(scales) # for axis and scale operations.

setwd("./");

records <- read.table("runninglog.csv", header=TRUE, sep=",");

p <- qplot(as.Date(records$Date, "%m/%d/%Y"), records$Distance/1000, color=records$Distance, size=records$Distance, main="Daily Running Distance (Miles) \n")
p <- p + scale_size_area()
p <- p + list(xlab("Date"), ylab("Distance (Miles)"));
p <- p + theme(legend.position="none")
print(p)


records <- read.table("runninglog.csv", header=TRUE, sep=",");
p1 <- qplot(as.Date(records$Date, "%m/%d/%Y"), records$Aggregated.Distance/1000, main="Aggregated Distance (Miles)\n")
p1 <- p1 + geom_line(size=0.8, color="#4C0099") + scale_shape_discrete(solid=T, guide="none")
p1 <- p1 + geom_point(shape=1, size=4, color="#CC0000") + scale_size_area()
p1 <- p1 + list(xlab("Date"), ylab("Distance (Miles)"));
p1 <- p1 + theme(legend.position="none")
p1 <- p1 + scale_x_date(breaks = "15 days", minor_breaks = "5 days", labels = date_format("%m.%d"))
p1 <- p1 + scale_y_continuous(breaks=seq(0, 550, 50))
print(p1)

