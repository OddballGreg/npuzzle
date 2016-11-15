<?php

function parse($fileName)
{
    $contents = file($fileName);
    $index = -1;
    while (isset($contents[++$index]))
        if (strlen(explode("#", $contents[$index])[0]) == 0)
            array_splice($contents, $index, 1);
    if (count($contents) < 4)
        die("Puzzle is too small.\n");
    $size = trim($contents[0]);
    if (is_array($size) == TRUE)
        die("Puzzle size not given.\n");
    else if ($size < 3)
        die("Puzzle is too small.\n");
    $GLOBALS['size'] = (int)trim($contents[0]);
    echo "global size " . $GLOBALS['size']."\n";
    $contents = array_splice($contents, 1);
    $hash = NULL;
    foreach ($contents as $line)
    {
        $line = explode("#", $line)[0];
        if (strlen($line) > 5) {
            $line = expload(" ", $line);
            $line = array_diff($line, [NULL]);
            $line = implode(" ", $line);
            $hash = $hash . trim($line) . ",";
        }
    }
    return (trim($hash, ',')); //Implement checks to make sure that the supplied puzzle is valid
}

function genPuzzle()
{
    $grid = array(array());
    $size = 3;
    $max = $size * $size - 1;

    $used = array();

    for ($xiter = 0; $xiter < $size; $xiter++) {
        for ($yiter = 0; $yiter < $size; $yiter++) {
            $newNum = rand(0, $max);
            while (in_array($newNum, $used)) {
                $newNum = rand(0, $max);
            }
            $grid[$xiter][$yiter] = $newNum;
            $used[] = $newNum;
        }
    }

    foreach ($grid as $row)
        $prehash[] = implode(" ", $row);
    $hash = implode(",", $prehash);
    return ($hash);

}

function isSolvable($grid)
{
    $max = $GLOBALS['size'] * $GLOBALS['size'] - 1;
    $inversions = 0;
    for ($x = 0; $x < $GLOBALS['size']; $x++) {
        for ($y = 0; $y < $GLOBALS['size']; $y++) {

            if ($grid[$x][$y] == 0)
                $blank = $y;
            else
                $line[] = $grid[$x][$y];

        }
    }
    print_r($line);
    for ($i = 0; $i < $max ; $i++) {
        for ($j = $i + 1; $j < $max; $j++) {
            if ($line[$i] > $line[$j]) {
                $inversions++;
            }
        }
    }
    echo "num inversions " . $inversions . "\n";
    if (($GLOBALS['size'] % 2 == 1 && $inversions % 2 == 1)) {
        echo "odd puzel even inverces\n";
        return true;
    }
    if ($GLOBALS['size'] % 2 == 0 && (($GLOBALS['size'] - $blank) % 2 != $inversions % 2)) {
        echo "even puzzel " . ($GLOBALS['size'] - $blank) % 2 . "\n";
        return true;
    }
    return false;
}

?>