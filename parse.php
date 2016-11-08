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

	$contents = array_splice($contents, 1);
	$hash = NULL;
	foreach ($contents as $line)
		$hash = $hash . trim($line) . ",";
	return (trim($hash, ','));
}

function setGoal()
{
	
}
?>