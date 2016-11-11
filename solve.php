<?php

function solve()
{
	if (strcmp($GLOBALS['osets'][0]->getHash(), $GLOBALS['sol']->getHash()) == 0)
		die ("Puzzle is already solved.\n");

	while (1)
	{ 
		foreach ($GLOBALS['osets'] as $node)
		{
			if (strncmp($node->getHash(), $GLOBALS['sol']->getHash(), strlen($GLOBALS['sol']->getHash())) == 0)
			{
				echo "Solution Found:\n";
				printSolution($node);
				die('\n');
			}
		}
		$cheapest = NULL;
		foreach ($GLOBALS['osets'] as $node)
		{
			echo $node . "\n";
			if ($cheapest == NULL)
				$cheapest = $node;
			if ($cheapest == NULL && $node->getFofX() < $cheapest->getFofX())
				$cheapest = $node;
		}
		if ($cheapest == NULL)
			die ("No open set found\n");
		$GLOBALS['osets'] = array_merge($GLOBALS['osets'], $cheapest->genMoves());
		//print_r($cheapest->genMoves());
		$GLOBALS['csets'][] = $cheapest;
		$index = -1;
		while (isset($GLOBALS['osets'][++$index]))
			if ($cheapest->getId() == $GLOBALS['osets'][$index]->getId())
				$GLOBALS['osets'] = array_diff($GLOBALS['osets'], [$cheapest]);
		echo "Closed Set: " . $cheapest . "\n";
	}
}

function printSolution($endNode)
{
	$pid = $endNode->getParent();
	foreach ($GLOBALS['osets'] as $node)
	{
		$tid = $node->getId();
		if ($tid = $pid)
		{
			echo $node . "\n";
			printSolution($node);
		}

	}
	foreach ($GLOBALS['csets'] as $node)
	{
		$tid = $node->getId();
		if ($tid = $pid)
		{
			echo $node . "\n";
			printSolution($node);
		}
	}
}

?>