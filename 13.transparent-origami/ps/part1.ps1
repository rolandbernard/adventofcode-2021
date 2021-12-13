
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

Write-Output ("Result: " + ($points | Use-Fold -Fold $folds[0] | Select-Object -Unique x, y).count)

