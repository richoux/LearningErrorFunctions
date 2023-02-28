using CSV
using DataFrames
using PrettyTables
using StatsPlots

df = DataFrame(CSV.File("results_2021-10-27.csv"))

pretty_table(df)

function format_name(problem)
    mark1 = findfirst("_", problem).start
    mark2 = findlast("_", problem).stop

    n = parse(Int, problem[1:mark1-1])
    family = problem[mark1+1:mark2-1]
    technique = problem[mark2+1:end]

    N = occursin("sudoku", family) ? n^2 : n

    return "$family $N×$N ($technique)" |> uppercasefirst
end

@df df plot(:problem, [:mean :median :min :max :std_dev :solutions], colour=[:red :blue])

# @df singers violin(:VoicePart, :Height, line=0, fill=(0.2, :blue))
# @df singers boxplot!(:VoicePart, :Height, line=(2, :black), fill=(0.3, :orange))
