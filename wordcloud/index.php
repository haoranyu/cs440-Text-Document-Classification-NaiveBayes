<?php
if(!isset($_GET['data'])){
	exit("please set ?data=(0/1/2/3/4/5/6/7)");
}
$data = file_get_contents('data.cloud/word.nostop.'.intval($_GET['data']).'.txt');
$word_array = explode("\n",$data);
$cloud_data = array();
foreach($word_array as &$word){
	$word = explode(":",$word);
	if(isset($word[1])){
		$word[1] *= 10000;
		if(intval($word[1]) > 0){
			array_push($cloud_data, array($word[0], sqrt(intval($word[1]))*10));
		}
	}
}
?>
<html>
<head>
<link rel="stylesheet" type="text/css" href="cloud.css">
<script src="http://code.jquery.com/jquery-latest.js" type="text/javascript" charset="utf-8"></script>
<script src="cloud.js" type="text/javascript" charset="utf-8"></script>
 <script type="text/javascript">
      var word_list = new Array(
		<?php foreach($cloud_data as $w){?>
        {text: "<?php echo $w[0]?>", weight: <?php echo $w[1]?>},
		<?php }?>
        {text: "", weight: 0}
      );
      $(document).ready(function() {
        $("#wordcloud").jQCloud(word_list);
      });
    </script>
	
<style type="text/css">
  body {
	margin:0;
	padding:0;
	background: #eee;
	font-family: Helvetica, Arial, sans-serif;
  }
  #wordcloud {
	margin: 30px auto;
	width: 100%;
	height: 100%;
	border: none;
  }
  #wordcloud span.w10, #wordcloud span.w9, #wordcloud span.w8, #wordcloud span.w7 {
	text-shadow: 0px 1px 1px #ccc;
  }
  #wordcloud span.w3, #wordcloud span.w2, #wordcloud span.w1 {
	text-shadow: 0px 1px 1px #fff;
  }
</style>
</head>
<body>
<div id="wordcloud"></div>

</body>