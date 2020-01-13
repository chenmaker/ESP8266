<?php
/*
 * Written By: ShivalWolf
 * Date: 2011/06/03
 * Contact: Shivalwolf@domwolf.net
 *
 * UPDATE 2011/04/05
 * The code now returns a real error message on a bad query with the mysql error number and its error message
 * checks for magic_quotes being enabled and strips slashes if it is. Its best to disable magic quotes still.
 * Checks to make sure the submitted form is a x-www-form-urlencode just so people dont screw with a browser access or atleast try to
 * Forces the output filename to be JSON to conform with standards
 *
 * UPDATE 2011/06/03
 * Code updated to use the Web Module instead of tinywebdb
 *
 * UPDATE 2013/12/26
 * minor modifications by Taifun
 */

/************************************CONFIG****************************************/
//DATABSE DETAILS//
$DB_ADDRESS="127.0.0.1:3307";
$DB_USER="STM";
$DB_PASS="k7902920";
$DB_NAME="chen";

//SETTINGS//
//This code is something you set in the APP so random people cant use it.
$SQLKEY="l0615";

/************************************CONFIG****************************************/

//these are just in case setting headers forcing it to always expire and the content type to CSV
//header('Cache-Control: no-cache, must-revalidate');
//header('Content-type: text/csv');

error_log(print_r($_GET,TRUE));

if( isset($_GET['query']) && isset($_GET['key']) ){         //checks if the tag GET is there and if its been a proper form GET
  if($_GET['key']==$SQLKEY){          ///validate the SQL key
    $query=urldecode($_GET['query']);
    if(GET_magic_quotes_gpc()){     //check if the worthless pile of crap magic quotes is enabled and if it is strip the slashes from the query
      $query=stripslashes($query);
    }
    $link = mysql_connect($DB_ADDRESS,$DB_USER,$DB_PASS);     //connect ot the MYSQL database
    mysql_select_db($DB_NAME,$link);                          //connect to the right DB
    if($link){
      $result=mysql_query($query);                            //runs the GETed query (NO PROTECTION FROM INJECTION HERE)
	  while($e=mysql_fetch_assoc($result))
				  $output[]=$e;
		   print(json_encode($output));  
	  /*
      if($result){
        if (strlen(stristr($query,"SELECT"))>0) {             //tests if its a select statemnet
          $num_fields = mysql_num_fields($result);            //collects the rows and writes out a header row
          $headers = array();
          for ($i = 0; $i < $num_fields; $i++) {
            $headers[] = mysql_field_name($result , $i);
          }
          $outstream = fopen("php://temp", 'r+');             //opens up a temporary stream to hold the data
          fputcsv($outstream, $headers, ',', '"');
          while ($row = mysql_fetch_row($result)){
            fputcsv($outstream, $row, ',', '"');
          }
          rewind($outstream);
          fpassthru($outstream);
          fclose($outstream);
          // echo $csv; //writes out csv data back to the client
        } else {
          header("HTTP/1.0 201 Rows");
          echo "AFFECTED ROWS: ".mysql_affected_rows($link); //if the query is anything but a SELECT it will return the number of affected rows

        }
      } else {
        header("HTTP/1.0 400 Bad Request");  //send back a bad request error
        echo mysql_errno($link).": ".mysql_error($link);     // errors if the query is bad and spits the error back to the client
      }
	  */
      mysql_close($link);                                    //close the DB
    } else {
      header("HTTP/1.0 400 Bad Request");
      echo "ERROR Database Connection Failed";               //reports a DB connection failure
    }
  } else {
     header("HTTP/1.0 400 Bad Request");
     echo "Bad Request";                                     //reports if the code is bad
  }
} else {
        header("HTTP/1.0 400 Bad Request");
        echo "Bad Request";
}

?>