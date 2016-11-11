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
		foreach ($GLOBALS['osets'] as $node)
		{
			if (strcmp($node->getHash(), $GLOBALS['sol']->getHash()) === 0)
            {
                echo $node->getHash() . " " . $GLOBALS['sol']->getHash() . "\n"; 
				echo "Solution Found:\n";
                printSolution($node);
                echo "Solution found in " . (time() - $time) . " seconds after " . $iterations . " iterations.\n";
				die('\n');
			}
		}
		$cheapest = NULL;
		foreach ($GLOBALS['osets'] as $node)
		{
			//echo $node . "\n";
			if ($cheapest == NULL)
				$cheapest = $node;
			if ($cheapest != NULL && $node->getFofX() < $cheapest->getFofX())
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
		echo $cheapest . "\n";
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
