var jsLectTemp;
var jsLectHum;
var jsEstEq1;
var jsEstEq2;
var jsEstTemp;
var jsEst220;
var	jsEstSec;
var jsEstModo;
var	jsEstDelaymed;
var jsProxConm;
var jsDivCr1;
var jsDivCr2;

var jsTipoCr1;
var jsReenc1;
var jsCompMode1;

var jsTipoCr2;
var jsReenc2;
var jsCompMode2;

var xmlDoc;
var xmlhttp;
var wPagina;
var Url;
function Read_XML_File(pagina)
{
	Url= "variables.xml" + "?nocache=" + new Date().getTime()
	wPagina=pagina;
	try {//Test for Internet Explorer
		xmlDoc=new ActiveXObject("Microsoft.XMLDOM");
		xmlDoc.async=false; //We want a synchronous connection
		xmlDoc.load(Url); //Load the XML file
	}catch(err){ //If ActiveX isn't going to work we use a more codified standard
		try {//Every browser but Internet Explorer
			xhttp=new XMLHttpRequest();
			xhttp.open("GET",Url,false);
    	    xhttp.send("");
			xmlDoc=xhttp.responseXML;
    	}catch(err){ //If that doesn't work, we produce an error mocking our user.
//			alert("Su explorador no es compatible con IneControl");
//			return;
		}

	}

   jsLectTemp = xmlDoc.getElementsByTagName("LectTemp")[0].childNodes[0].nodeValue;
	jsLectHum = xmlDoc.getElementsByTagName("LectHum")[0].childNodes[0].nodeValue;
	jsEstEq1 = xmlDoc.getElementsByTagName("EstEq1")[0].childNodes[0].nodeValue;
	jsEstEq2 = xmlDoc.getElementsByTagName("EstEq2")[0].childNodes[0].nodeValue;
   jsEstTemp = xmlDoc.getElementsByTagName("EstTemp")[0].childNodes[0].nodeValue;
	jsEst220 = xmlDoc.getElementsByTagName("Est220")[0].childNodes[0].nodeValue;
	jsEstSec = xmlDoc.getElementsByTagName("EstSec")[0].childNodes[0].nodeValue;
 	jsEstModo = xmlDoc.getElementsByTagName("EstModo")[0].childNodes[0].nodeValue;
	jsEstDelayMed = xmlDoc.getElementsByTagName("EstDelayMed")[0].childNodes[0].nodeValue;
	jsProxConm = xmlDoc.getElementsByTagName("ProxConm")[0].childNodes[0].nodeValue;
	jsDivCr1 = xmlDoc.getElementsByTagName("DivCr1")[0].childNodes[0].nodeValue;
	jsDivCr2 = xmlDoc.getElementsByTagName("DivCr2")[0].childNodes[0].nodeValue;
  	
	jsTipoCr1 = xmlDoc.getElementsByTagName("TipoCr1")[0].childNodes[0].nodeValue;
	jsReenc1 = xmlDoc.getElementsByTagName("Reenc1")[0].childNodes[0].nodeValue;
	jsCompMode1 = xmlDoc.getElementsByTagName("CompMode1")[0].childNodes[0].nodeValue;

	jsTipoCr2 = xmlDoc.getElementsByTagName("TipoCr2")[0].childNodes[0].nodeValue;
	jsReenc2 = xmlDoc.getElementsByTagName("Reenc2")[0].childNodes[0].nodeValue;
	jsCompMode2 = xmlDoc.getElementsByTagName("CompMode2")[0].childNodes[0].nodeValue;
	

	
	document.getElementById("idLectTemp").innerHTML=jsLectTemp;
	document.getElementById("idLectHum").innerHTML=jsLectHum;
	document.getElementById("idEstEq1").innerHTML=jsEstEq1;
	document.getElementById("CeldaEq1").className=jsEstEq1;
	document.getElementById("idEstEq2").innerHTML=jsEstEq2;
	document.getElementById("CeldaEq2").className=jsEstEq2;
	document.getElementById("idEstTemp").innerHTML=jsEstTemp;
	document.getElementById("CeldaTemp").className=jsEstTemp;
	document.getElementById("idEst220").innerHTML=jsEst220;
	document.getElementById("Celda220").className=jsEst220;
	document.getElementById("idEstSec").innerHTML=jsEstSec;
	document.getElementById("CeldaSec").className=jsEstSec;
	document.getElementById("idEstModo").innerHTML=jsEstModo;
	document.getElementById("CeldaModo").className=jsEstModo;
	document.getElementById("idEstDelay").innerHTML=jsEstDelayMed;
	document.getElementById("CeldaDelay").className=jsEstDelayMed;
	document.getElementById("idProxConm").innerHTML=jsProxConm;

   if (wPagina==='IRLEARN'){

		if (jsTipoCr1!=0 && jsReenc1!=0){
			document.getElementById("btGrCr1on").disabled=false;	
			document.getElementById("btTestCr1on").disabled=false;				
			document.getElementById("btGrCr1off").disabled=false;			
			document.getElementById("btTestCr1off").disabled=false;										
			if (jsTipoCr1==2) {	// es del tipo TV por lo que hay que grabar el reencendido					
				document.getElementById("btGrCr1reenc").disabled=false;
				document.getElementById("btTestCr1reenc").disabled=false;
			}else{
				document.getElementById("btGrCr1reenc").disabled=true;
				document.getElementById("btTestCr1reenc").disabled=true;
			}

		}else{
			document.getElementById("btGrCr1on").disabled=true;	
			document.getElementById("btTestCr1on").disabled=true;				
			
			document.getElementById("btGrCr1reenc").disabled=true;
			document.getElementById("btTestCr1reenc").disabled=true;							

			document.getElementById("btGrCr1off").disabled=true;			
			document.getElementById("btTestCr1off").disabled=true;										
			
		}
		
		if (jsTipoCr2!=0 && jsReenc2!=0){
			document.getElementById("btGrCr2on").disabled=false;	
			document.getElementById("btTestCr2on").disabled=false;				

			document.getElementById("btGrCr2off").disabled=false;			
			document.getElementById("btTestCr2off").disabled=false;										


			if (jsTipoCr2==2) {	// es del tipo TV por lo que hay que grabar el reencendido					
				document.getElementById("btGrCr2reenc").disabled=false;
				document.getElementById("btTestCr2reenc").disabled=false;
			}else{
				document.getElementById("btGrCr2reenc").disabled=true;
				document.getElementById("btTestCr2reenc").disabled=true;
			}


		}else{
			document.getElementById("btGrCr2on").disabled=true;	
			document.getElementById("btTestCr2on").disabled=true;				
			
			document.getElementById("btGrCr2reenc").disabled=true;
			document.getElementById("btTestCr2reenc").disabled=true;							

			document.getElementById("btGrCr2off").disabled=true;			
			document.getElementById("btTestCr2off").disabled=true;										
			
		}
		
		
		document.getElementById("idDivCr1").innerHTML=jsDivCr1;
		document.getElementById("idDivCr2").innerHTML=jsDivCr2;
	}

  	setTimeout("Read_XML_File(wPagina)",3000);
//Store the value of My_Data tag in the XML_Data variable
}

function alerta(mensaje,cgi_redirect)
{
	alert(mensaje);
	location.href=cgi_redirect;

}


function EnviarForm(nombre_form)
{
	document.getElementById(nombre_form).submit();
}


function MM_openBrWindow(theURL,winName,features) { //v2.0
  window.open(theURL,winName,features);
}