
data <- read.delim("/home/roland/Workspace/adventofcode-2021/01.sonar-sweep/input.txt", header = FALSE, sep = ",")[,1]

n <- 0
for (x in 2:length(data)) {
    if (data[x - 1] < data[x]) {
        n <- n + 1
    }
}

print(paste("Result:", n))

