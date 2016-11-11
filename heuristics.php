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

function euclidean()
{

}

function manhattan()
{

}

?>