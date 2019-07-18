library(chebpol)

values <- c(2.3, 1.2, 1.1, 1.2, 1.1, 0, 1.1, 0, 1.1,
            1.2, 1.1, 0, 1.1, 2.2, 1.1, 0, 1.1, 1.2,
            1.1, 0, 1.1, 0, 1.1, 1.2, 1.1, 1.2, 2.3)

ch <- ipol(values, dims=c(3,3,3), intervals=list(c(0,2),c(0,2),c(0,2)), method='uniform')

ch(c(1,1,1))

data <- read.csv(file="/home/jeff/Téléchargements/Attachments-Fichers CSV/all-diff_4.csv")
hamming <- c(data[,1])
manhattan <- c(data[,2])
mix <- c(data[,3])

knots <- matrix(data=NA, nrow=4, ncol=length(mix))
knots[1,] = data[,4]
knots[2,] = data[,5]
knots[3,] = data[,6]
knots[4,] = data[,7]

ad4 <- ipol(mix, knots=knots, k=2, method="polyharmonic")
ad4(c(0,2,3,1))

data <- read.csv(file="/home/jeff/Téléchargements/Attachments-Fichers CSV/all-diff_5.csv")
hamming <- c(data[,1])
manhattan <- c(data[,2])
mix <- c(data[,3])

knots <- matrix(data=NA, nrow=5, ncol=length(mix))
knots[1,] = data[,4]
knots[2,] = data[,5]
knots[3,] = data[,6]
knots[4,] = data[,7]
knots[5,] = data[,8]

ad5 <- ipol(mix, knots=knots, k=2, method="polyharmonic")
ad5(c(0,2,3,1,4))

data <- read.csv(file="/home/jeff/Téléchargements/Attachments-Fichers CSV/all-diff_6.csv")
hamming <- c(data[,1])
manhattan <- c(data[,2])
mix <- c(data[,3])

knots <- matrix(data=NA, nrow=6, ncol=length(mix))
knots[1,] = data[,4]
knots[2,] = data[,5]
knots[3,] = data[,6]
knots[4,] = data[,7]
knots[5,] = data[,8]
knots[6,] = data[,9]

## Uncomment only if testing the limit of chebpol (size of vectors)
# ad6 <- ipol(mix, knots=knots, k=2, method="polyharmonic")
# ad6(c(0,2,3,1,5,4))
#
# data <- read.csv(file="/home/jeff/Téléchargements/Attachments-Fichers CSV/less_than_3.csv")
# hamming <- c(data[,1])
# manhattan <- c(data[,2])
# mix <- c(data[,3])
#
# knots <- matrix(data=NA, nrow=3, ncol=length(mix))
# knots[1,] = data[,4]
# knots[2,] = data[,5]
# knots[3,] = data[,6]

lt3 <- ipol(mix, knots=knots, k=2, method="polyharmonic")
lt3(c(0,2,3))

data <- read.csv(file="/home/jeff/Téléchargements/Attachments-Fichers CSV/less_than_4.csv")
hamming <- c(data[,1])
manhattan <- c(data[,2])
mix <- c(data[,3])

knots <- matrix(data=NA, nrow=4, ncol=length(mix))
knots[1,] = data[,4]
knots[2,] = data[,5]
knots[3,] = data[,6]
knots[4,] = data[,7]

lt4 <- ipol(mix, knots=knots, k=2, method="polyharmonic")
lt4(c(0,2,3,1))

## Uncomment only if testing speed limits of chebpol
# data <- read.csv(file="/home/jeff/Téléchargements/Attachments-Fichers CSV/less_than_5.csv")
# hamming <- c(data[,1])
# manhattan <- c(data[,2])
# mix <- c(data[,3])
#
# knots <- matrix(data=NA, nrow=5, ncol=length(mix))
# knots[1,] = data[,4]
# knots[2,] = data[,5]
# knots[3,] = data[,6]
# knots[4,] = data[,7]
# knots[5,] = data[,8]
#
# lt5 <- ipol(mix, knots=knots, k=2, method="polyharmonic")
# lt5(c(0,2,3,1,5))
