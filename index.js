// https://sheetdb.io/api/v1/9lh0a1lob0uhw
$('table tr').each(function(){
    $(this).find('th').first().addClass('first');
    $(this).find('th').last().addClass('last');
    $(this).find('td').first().addClass('first');
    $(this).find('td').last().addClass('last');
  });
  
  $('table tr').first().addClass('row-first');
  $('table tr').last().addClass('row-last');