
$raw = $Input | Join-String -Separator "|"
$split = $raw.Split("||")
$points = $split[0].Split("|") | ForEach-Object {,($_.Split(","))} | ForEach-Object {@{x = [int]$_[0]; y = [int]$_[1]}}
$folds = $split[1].Split("|") | ForEach-Object {,($_.Split("="))} | ForEach-Object {@{d = $_[0][-1]; v = [int]$_[1]}}

function Use-Fold {
    param ($Fold)
    if ($Fold.d -eq "x") {
        $Input | ForEach-Object {
            if ($_.x -gt $Fold.v) {@{x = 2*$Fold.v - $_.x; y = $_.y}} else {$_}
        }
    } else {
        $Input | ForEach-Object {
            if ($_.y -gt $Fold.v) {@{x = $_.x; y = 2*$Fold.v - $_.y}} else {$_}
        }
    }
}

foreach ($fold in $folds) {
    $points = ($points | Use-Fold -Fold $fold)
}

$points = ($points | Select-Object -Unique x, y)

Write-Output "Result:"

for ($i = 0; $i -lt 6; $i++) {
    for ($j = 0; $j -lt 39; $j++) {
        if ($points | Where-Object {$_.x -eq $j -and $_.y -eq $i}) {
            Write-Host -NoNewline "#"
        } else {
            Write-Host -NoNewline "."
        }
    }
    Write-Host
}

