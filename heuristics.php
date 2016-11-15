<?php

function hamming($node, $solution)
{
	$prenhash = explode(",", $node->getHash());
	$preshash = explode(",", $solution->getHash());
	$nhash = array();
	$shash = array();
	//possibly less expensive way. 2 indexes for each hash after strsplit, compare individual numbers while ignoring spaces and commas.
	foreach ($prenhash as $line) 
		$nhash = array_merge($nhash, explode(' ', $line)); 
	foreach ($preshash as $line) 
		$shash = array_merge($shash, explode(' ', $line)); 
	$index = -1;
	$cost = 0;
	while (isset($nhash[++$index]))
		if ($nhash[$index] != $shash[$index])
			$cost++;
	return($cost);
}

function euclidean($node, $solution)
{
	$ngrid = $node->getGrid();
	$sgrid = $solution->getGrid();
	$preshash = explode(",", $solution->getHash());
	$shash = array();
	foreach ($preshash as $line) 
		$shash = array_merge($shash, explode(' ', $line));
	foreach ($shash as $value)
	{
		$sxy = findxy($sgrid, $value);
		$nxy = findxy($ngrid, $value);
		$cost[] = sqrt(pow(($sxy['x'] - $nxy['x']),2) + pow(($sxy['y'] - $nxy['y']),2)); // Euclidean Distance requires refactoring
	}
	return(floor(array_sum($cost)));
}

function manhattan($node, $solution)
{
	$ngrid = $node->getGrid();
	$sgrid = $solution->getGrid();
	$preshash = explode(",", $solution->getHash());
	$shash = array();
	foreach ($preshash as $line) 
		$shash = array_merge($shash, explode(' ', $line));
	foreach ($shash as $value)
	{
	    if ($value != 0) {
            $sxy = findxy($sgrid, $value);
            $nxy = findxy($ngrid, $value);
            $new['x'] = abs($sxy['x'] - $nxy['x']);
            $new['y'] = abs($sxy['y'] - $nxy['y']);
            $cost[] = $new['y'] + $new['x'];
        }
	}
	return(array_sum($cost));
}

function findxy($grid, $number)
{
	$x = -1;
		while (isset($grid[++$x]))
		{
			$y = -1;
			while (isset($grid[$x][++$y]))
				if ($grid[$x][$y] == $number)
					return(['x' => $x, 'y' => $y]);
		}
	return (FALSE);
}

?>
