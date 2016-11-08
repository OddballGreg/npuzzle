<?php

/*php error reporting code, remove before submission                               */
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

if ($argc < 2)
	die("Too few arguements given\n");
if (file_exists($argv[1]) == FALSE)
	die("File does not exit\n");



?>