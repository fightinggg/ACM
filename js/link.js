// 背景
var random = Math.round(Math.random() * 10);
if (window.innerWidth > 1000) {
    document.write('<style>body{ background-image: url(/ACM/img/' + random + '.jpg);!important;}</style>');
}

function codespan(file) {
    var reader = new FileReader();//new一个FileReader实例
    reader.readAsText(file[0]);
    reader.onload = function () {
        return this.result;
    }
}


document.writeln('   <link rel="stylesheet" type="text/css"  href="/ACM/css/head.css">');
document.writeln('<link rel="stylesheet" href="/ACM/css/head_phone.css" type="text/css" media="screen and (max-width: 999px)">')
document.writeln('   <link rel="stylesheet" type="text/css"  href="/ACM/css/pastebin.css">');
document.writeln('   <link rel="stylesheet" type="text/css"  href="/ACM/css/code.css">');

//自动提交
document.writeln("    <script>(function(){var bp = document.createElement('script');var curProtocol = window.location.protocol.split(':')[0];if (curProtocol === 'https'){bp.src = 'https://zz.bdstatic.com/linksubmit/push.js';}else{bp.src = 'http://push.zhanzhang.baidu.com/push.js';}var s = document.getElementsByTagName(\"script\")[0];s.parentNode.insertBefore(bp, s);})();</script>")





