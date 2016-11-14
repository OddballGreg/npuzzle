<?php

function solve()
{
	if (strcmp($GLOBALS['osets'][0][0]->getHash(), $GLOBALS['sol']->getHash()) == 0)
        die ("Puzzle is already solved.\n");

    $time = time();
    $iterations = 0;
	while (1)
    { 
        $iterations++;
		$cheapest = NULL;
		$fofx = 0;
		while ($cheapest == NULL)
		{
			echo $fofx . "\n";
			if (array_key_exists($fofx, $GLOBALS['osets']))
				if ($GLOBALS['osets'][$fofx][0] == NULL)
					unset($GLOBALS['osets'][$fofx]);
			if (is_array($GLOBALS['osets'][$fofx]))
			{
				echo "Array found\n";
				foreach ($GLOBALS['osets'][$fofx] as $node)
				{
					if ($cheapest == NULL)
						$cheapest = $node;
					if ($cheapest != NULL && $node->getFofX() < $cheapest->getFofX())
						$cheapest = $node;
				}
			}
			$fofx++;
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
		{	
			echo $new->getFofX . PHP_EOL;
			$GLOBALS['osets'][$new->getFofX][] = $new;
		}

		//Add cheapest to closed sets and remove from open sets
		$GLOBALS['csets'][] = $cheapest;
		$index = -1;
		while (isset($GLOBALS['osets'][$fofx][++$index]))
			if ($cheapest->getId() === $GLOBALS['osets'][$fofx][$index]->getId())
				array_splice($GLOBALS['osets'][$fofx], $index, 1);
		if ($GLOBALS['verb'] == 1)
		{
			echo $cheapest . "\n";
			echo $iterations . " iterations.\n";
		}
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
