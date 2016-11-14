<?php

function solve()
{
	if (strcmp($GLOBALS['osets'][0]->getHash(), $GLOBALS['sol']->getHash()) == 0)
        die ("Puzzle is already solved.\n");

    $time = time();
    $iterations = 0;
	while (1)
    { 
        $iterations++;
		$cheapest = NULL;
		foreach ($GLOBALS['osets'] as $node)
		{
			if ($cheapest == NULL)
				$cheapest = $node;
			if ($cheapest != NULL && $node->getFofX() < $cheapest->getFofX())
				$cheapest = $node;
		}
		if ($cheapest == NULL)
            die ("No open set found\n");

		//Get new moves from cheapest node, compare to solution and add to open sets
		$newnodes = $cheapest->genMoves();
		//print_r($cheapest->genMoves());
		//print_r($newnodes);
		foreach ($newnodes as $node)
		{
			if (strcmp($node->getHash(), $GLOBALS['sol']->getHash()) === 0)
            {
				echo "Solution Found:\n";
                printSolution($node);
				echo $GLOBALS['csets'][0];
                echo "\nSolution found in " . (time() - $time) . " second(s) after " . $iterations . " iteration(s).\n";
				die("\n");
			}
		}
		
		foreach ($newnodes as $new)
			$GLOBALS['osets'][] = $new;

		//Add cheapest to closed sets and remove from open sets
		$GLOBALS['csets'][] = $cheapest;
		$index = -1;
		while (isset($GLOBALS['osets'][++$index]))
			if ($cheapest->getId() === $GLOBALS['osets'][$index]->getId())
				array_splice($GLOBALS['osets'], $index, 1);
		if ($GLOBALS['verb'] == 1)
			echo $cheapest . "\n";
		else if ($iterations % 100 == 0)
			echo ".";
	}
}

function printSolution($endNode)
{
    echo $endNode . "\n";
	$pid = $endNode->getParent();
	foreach ($GLOBALS['osets'] as $node)
	{
		$tid = $node->getId();
		if ($tid != NULL && $tid == $pid)
			printSolution($node);

	}
	foreach ($GLOBALS['csets'] as $node)
	{
		$tid = $node->getId();
		if ($tid != NULL && $tid == $pid)
			printSolution($node);
	}
}

?>
