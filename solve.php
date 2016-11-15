<?php

function solve()
{
    if (strcmp($GLOBALS['osets'][0]->getHash(), $GLOBALS['sol']->getHash()) == 0)
        die ("Puzzle is already solved.\n");

    $time = time();
    $iterations = 0;
    $nodes = 1;
    $GLOBALS['checked'][] = $GLOBALS['osets'][0]->getHash();
    while (1) {
        //get the chepest openset
        $iterations++;
        unset($cheapest);
        foreach ($GLOBALS['osets'] as $node) {
            if (!isset($cheapest))
                $cheapest = $node;
            if ($GLOBALS['algo'] == ASTAR) {
                if (isset($cheapest) && $node->getFofX() <= $cheapest->getFofX())
                    $cheapest = $node;
            } else if ($GLOBALS['algo'] == GREEDY) {
                if (isset($cheapest) && $node->getCost() < $cheapest->getCost())
                    $cheapest = $node;
            } else if ($GLOBALS['algo'] == DEPTHFIRST) {
                $cheapest = end($GLOBALS['osets']);
            } else //breadthfirst
                break;
        }
        if ($cheapest == NULL)
            die ("No open set found\n");

       /* if ($GLOBALS['verb'] == 1){
            echo "chose:\n ".$cheapest."\nfrom:\n";
            foreach ($GLOBALS['osets'] as $node) {
                echo $node."\n";
            }
            echo "\n";
        }*/
        //Get new moves from cheapest node, compare to solution and add to open sets
        $newnodes = $cheapest->genMoves();
        //print_r($cheapest->genMoves());
        //print_r($newnodes);
        foreach ($newnodes as $node) {
            if (strcmp($node->getHash(), $GLOBALS['sol']->getHash()) === 0) {
                echo "Solution Found:\n";
                echo $GLOBALS['csets'][0] . "\n";
                printSolution($node);
                echo "\nSolution found in " . (time() - $time) . " second(s) after " . $iterations . " iteration(s).\n";
                echo "{$nodes} nodes were generated in order to find the " . $node->getDist() . " moves of the solution.\n";
                echo "open list: " . sizeof($GLOBALS['osets']) . " closed set " . sizeof($GLOBALS['csets']) . " \n";
                die("\n");
            }
        }

        foreach ($newnodes as $new) {
            $GLOBALS['osets'][] = $new;
            $GLOBALS['checked'][] = $new->getHash();
            $nodes++;
        }

        //Add cheapest to closed sets and remove from open sets
        $GLOBALS['csets'][] = $cheapest;
        $index = -1;
        while (isset($GLOBALS['osets'][++$index]))
            if ($cheapest->getId() === $GLOBALS['osets'][$index]->getId())
                array_splice($GLOBALS['osets'], $index, 1);


        if ($GLOBALS['verb'] == 1)
            //echo $cheapest . "\n";
            ;
        else if ($iterations % 100 == 0)
            echo ".";
    }
}

function printSolution($endNode)
{
    $pid = $endNode->getParent();
    foreach ($GLOBALS['osets'] as $node) {
        $tid = $node->getId();
        if ($tid != NULL && $tid == $pid)
            printSolution($node);

    }
    foreach ($GLOBALS['csets'] as $node) {
        $tid = $node->getId();
        if ($tid != NULL && $tid == $pid)
            printSolution($node);
    }
    echo $endNode . "\n";
}

?>
