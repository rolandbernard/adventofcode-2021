<?php
$freq_map = array(
    42 => 0, 17 => 1, 34 => 2, 39 => 3, 30 => 4,
    37 => 5, 41 => 6, 25 => 7, 49 => 8, 45 => 9,
);

$count = 0;
while ($l = fgets(STDIN)) {
    $split = explode(' | ', $l);
    $pattern = explode(' ', $split[0]);
    $numbers = explode(' ', $split[1]);
    $freq = array('a' => 0, 'b' => 0, 'c' => 0, 'd' => 0, 'e' => 0, 'f' => 0, 'g' => 0);
    foreach ($pattern as $pat) {
        foreach (str_split($pat) as $c) {
            $freq[$c]++;
        }
    }
    $value = 0;
    foreach ($numbers as $number) {
        $sum = 0;
        foreach (str_split(trim($number)) as $c) {
            $sum += $freq[$c];
        }
        $value = 10 * $value + $freq_map[$sum];
    }
    $count += $value;
}
?>
<?= $count ?>

