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

	$GLOBALS['size'] = (int)trim($contents[1]);
	$contents = array_splice($contents, 1);
	$hash = NULL;
	foreach ($contents as $line)
	{
		$line = explode("#", $line)[0];
		if (strlen($line) > 5)
			$hash = $hash . trim($line) . ",";
	}
	return (trim($hash, ',')); //Implement checks to make sure that the supplied puzzle is valid
}

?>