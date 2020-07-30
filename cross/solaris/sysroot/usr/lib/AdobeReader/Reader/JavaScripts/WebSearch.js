

/*
	==========================================================================
	Module: WebSearch.js
	==========================================================================
	The Software, including this file, is subject to the End User License
	Agreement.
	Copyright (c) 2005, Adobe Systems Incorporated, All Rights Reserved.
	==========================================================================
*/

function SearchGetURLVersion()
{/* returns the WebSearch.js file version number */
	return 1;
}

function SearchBuildURL(query, mode, country, vender, pdfOnly)
{/* Builds a URL for searching the web.

	Parameters:
		query: string to be searched such as "find newport"
		mode:  one of the search modes, kMatchPhrase, kMatchAllWords, or kMatchAnyWords.
		country: 3 character string such as "ENU", describing the country.
		vender: vender string specifier.  Used to select which URL to build
		pdfOnly: indicates search for PDFs only, otherwise don't limit search
*/
	var url, queryStr;

	if (mode < 0 || mode > 2)
		return "";

	
	switch (vender)
	{
		case 0:	/* yahoo */
		{

			/* country specific site addressing */
			if (country == "ENU")
				countryURL = "search.yahoo.com/search";
			else if (country == "DEU")
				countryURL = "de.search.yahoo.com/search";
			else if (country == "FRA")		 
				countryURL = "fr.search.yahoo.com/search";
			else if (country == "ITA")
				countryURL = "it.search.yahoo.com/search";
			else if (country == "NLD")
				countryURL = "nl.search.yahoo.com/search";		/* Neatherlands */
			else if (country == "ESP")
				countryURL = "es.search.yahoo.com/search";
			else if (country == "SVE")
				countryURL = "se.search.yahoo.com/search";		/* Swedish */
			else if (country == "JPN")
				countryURL = "search.yahoo.co.jp/bin/search";
			else if (country == "KOR")
				countryURL = "kr.search.yahoo.com/search";
			else if (country == "CHT")		 
				countryURL = "tw.search.yahoo.com/search";
			else if (country == "CHS")
				countryURL = "cn.websearch.yahoo.com/search/web_cn";
			else if (country == "PTB")
				countryURL = "br.search.yahoo.com/search";
			else if (country == "DAN")
				countryURL = "dk.search.yahoo.com/search";		/* Danish */
			else if (country == "SUO")
				countryURL = "fi.search.yahoo.com/search";		/* Finish */
			else if (country == "NOR")
				countryURL = "no.search.yahoo.com/search";		/* Norwegian */
			else if (country == "ARA")
				countryURL = "search.yahoo.com/search";			/* No Arabian */
			else if (country == "HEB")
				countryURL = "search.yahoo.com/search";			/* No Hebrew */
			else
				countryURL = "search.yahoo.com/search";


			url = "http://" + countryURL + "?fr=read";
			if (country == "JPN")
				url = url + "&ei=utf-8";
			else
				url = url + "&ei=UTF-8";
				
			queryStr = "";
			
			for (i=0; i < query.length; i++)
				if (query.charAt(i) == ' ')
					queryStr = queryStr + '+';
				else
					queryStr = queryStr + query.charAt(i);
			
			if (country == "JPN" || country == "KOR" || country == "CHT" || country == "CHS")
			{
				url = url + "&p=" + queryStr;
			}
			else
			{
				switch (mode)
				{
					case 0: /* kMatchPhrase */ 
						url = url + "&va=&va_vt=any&vp=" + queryStr + "&vp_vt=any&vo=&vo_vt=any";
						break;
					case 1: /* kMatchAllWords */ 
						url = url + "&va=" + queryStr + "&va_vt=any&vp=&vp_vt=any&vo=&vo_vt=any";
						break;
					case 2: /* kMatchAnyWords */ 
						url = url + "&va=&va_vt=any&vp=&vp_vt=any&vo=" + queryStr + "&vo_vt=any";
						break;
				}
			}
			
			
			if (pdfOnly)
				url = url + "&vf=pdf";
			else
				url = url + "&vf=all";
						
			break;
		}
		
		default:
			url = "error bad vender";
	}

	return url;
}
