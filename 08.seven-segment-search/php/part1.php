<?php
$count = 0;
while ($l = fgets(STDIN)) {
    $split = explode(' | ', $l);
    $pattern = explode(' ', $split[0]);
    $numbers = explode(' ', $split[1]);
    foreach ($numbers as $number) {
        if (in_array(strlen(trim($number)), array(2, 3, 4, 7))) {
            $count++;
        }
    }
}
?>
<?= $count ?>

