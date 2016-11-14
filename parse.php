<?php

function parse($fileName)
{
    $contents = file($fileName);
    if (count($contents) < 4)
        die("Puzzle is too small.\n");
    $size = trim($contents[0]);
    if (is_array($size) == TRUE)
        die("Puzzle size not given.\n");
    else if ($size < 3)
        die("Puzzle is too small.\n");

    $GLOBALS['size'] = (int)trim($contents[0]);
    $contents = array_splice($contents, 1);
    $hash = NULL;
    foreach ($contents as $line)
        $hash = $hash . trim($line) . ",";
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
    $line = array($GLOBALS['size'] * $GLOBALS['size']);
    $max = $GLOBALS['size'] * $GLOBALS['size'];
    $inversions = 0;
    for ($y = 0; $y < $GLOBALS['size']; $y++) {
        for ($x = 0; $x < $GLOBALS['size']; $x++) {
            $line[] = $grid[$x][$y];
            if ($grid[$x][$y] == 0)
                $blank = $y;
        }
    }
    for ($i = 0; $i < $max - 1; $i++) {
        for ($j = $i + 1; $j < $max; $j++) {
            if ($line[$i] > $line[$j] && $line[$i] != 0 && $line[$j] != 0)
                $inversions++;
        }
    }
    if (($GLOBALS['size'] % 2 == 1 && $inversions % 2 == 0)) {
        echo "odd puzel even inverces\n";
        return true;
    }
    if ($GLOBALS['size'] % 2 == 0 && (($GLOBALS['size'] - $blank) % 2 == $inversions % 2)) {
        echo "even puzzel ". ($GLOBALS['size'] - $blank) % 2 . "\n";
        return true;
    }
    return false;
}

?>