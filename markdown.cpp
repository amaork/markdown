#include "markdown.h"

/**************************************************************************************
	Markdown syntax, static data members
**************************************************************************************/
const string Markdown::syntax_data			=	"data";
const string Markdown::syntax_attr			=	"attr";

const string Markdown::title_syntax 		= 	"#";
const string Markdown::hrule_syntax 		= 	"------";
const string Markdown::strong_syntax 		= 	"__data__";
const string Markdown::emphasize_syntax		= 	"_data_";
const string Markdown::underline_syntax	 	= 	"<u>data</u>";
const string Markdown::strikethrough_syntax	=	"<s>data</s>";
const string Markdown::superscript_syntax	=	"<sup>data</sup>";
const string Markdown::subscript_syntax		=	"<sub>data</sub>";
const string Markdown::inlinecode_syntax	= 	"<p><code>data</code></p>";
const string Markdown::codeblock_syntax		=	"    ";	
const string Markdown::quote_syntax			= 	">";
const string Markdown::comment_syntax		=	"<!--data-->";
const string Markdown::nestedlist_syntax	=	"\t";
const string Markdown::orderedlist_syntax	=	"attr. data";
const string Markdown::unorderedlist_syntax	=	"+ data";
const string Markdown::fontcolor_syntax		=	"<font color=attr>data</font>";
const string Markdown::color_start_syntax	=	"<font color=data>";
const string Markdown::color_end_syntax		=	"</font>";
const string Markdown::link_syntax			=	"[data](attr)";
const string Markdown::image_syntax			=	"![data](attr)";
const string Markdown::anchor_syntax		=	"<a id=\"attr\">data</a>";
const string Markdown::intjump_syntax		=	"[data](#attr)";

const unsigned int Markdown::max_title_level		=	6;
const unsigned int Markdown::max_quote_level		=	12; 
const unsigned int Markdown::max_nestedlist_level	=	12;


/**************************************************************************************
	@brief	:	Constructor and destructor
**************************************************************************************/
void Markdown::init(void)
{
	/* Url and context split character */
	split_ch = " \t\n";

	/* Link start  */	
	link_start.push_back("www.");
	link_start.push_back("ftp://");
	link_start.push_back("http://");
	link_start.push_back("https://");

	/* Image end */
	image_end.push_back(".bmp");
	image_end.push_back(".png");
	image_end.push_back(".gif");
	image_end.push_back(".jpg");
	image_end.push_back(".jpeg");
	image_end.push_back(".tiff");
}

Markdown::Markdown(void)
{
	init();
}

Markdown::Markdown(const string& filename)
{
	string output_name = filename;

	/* Internal init */
	init();

	/* Check if filename has *.md extend */	
	if (filename.find(".md") == string::npos && filename.find(".markdown") == string::npos){

		output_name += ".md";
	}

	/* Create markdown file */
	md_output.open(output_name.c_str());

	/* Check if markdown file is opened */
	if (md_output.is_open()){

		cout << "Markdown file: " << filename << " is opend." << endl;
	}
	else{

		cerr << "Markdown file: " << filename << " open failed!" << endl;
	}

}


Markdown::~Markdown(void)
{
	if (md_output.is_open()){

		md_output.close();
	}
}

/**************************************************************************************
	@brief	:	Syntax generator, replace of syntax_data with data, if syntax_data do
				not found, append data to syntax 
**************************************************************************************/
string Markdown::syntax_generator(const string& syntax, const string& data)
{
	string syntax_with_data = syntax;	

	/* Check syntax */
	if (syntax.find(syntax_data) != string::npos){

		/* Into data to syntax */
		syntax_with_data.replace(syntax.find(syntax_data), syntax_data.size(), data);
	}
	else{

		syntax_with_data = syntax + data;
	}

	#ifdef	DEBUG
	cout << "SYNTAX IN:\t" << syntax << "[" << data << "]" << endl;
	cout << "SYNTAX_OUT:\t"<< syntax_with_data << endl;
	#endif

	return syntax_with_data;
}


/**************************************************************************************
	@brief	:	Syntax generator, replace of syntax_data with data, and replace of 
				syntax_attr with attr
**************************************************************************************/
string Markdown::syntax_generator(const string& syntax, const string& attr, const string& data)
{
	string::size_type attr_pos, data_pos;
	string syntax_with_data, syntax_with_attr;
	string syntax_with_data_and_attr = syntax;

	/* Get attribute and data postion */
	attr_pos = syntax.find(syntax_attr);
	data_pos = syntax.find(syntax_data);

	/* Check syntax */
	if (attr_pos != string::npos && data_pos != string::npos){

		/* Attr at before */
		if (attr_pos < data_pos){

			/* Split syntax as two part */
			syntax_with_attr = syntax.substr(0, attr_pos + syntax_attr.size());
			syntax_with_data = syntax.substr(attr_pos + syntax_attr.size());

			/* Replacement them for each */
			syntax_with_attr.replace(syntax_with_attr.find(syntax_attr), syntax_attr.size(), attr);
			syntax_with_data.replace(syntax_with_data.find(syntax_data), syntax_data.size(), data);

			/* Merger data and attr together */
			syntax_with_data_and_attr = syntax_with_attr + syntax_with_data;
			
		}
		/* Data at before*/
		else{
		
			/* Split syntax as two part */
			syntax_with_data = syntax.substr(0, data_pos + syntax_data.size());
			syntax_with_attr = syntax.substr(data_pos + syntax_data.size());

			/* Replacement them for each */
			syntax_with_data.replace(syntax_with_data.find(syntax_data), syntax_data.size(), data);
			syntax_with_attr.replace(syntax_with_attr.find(syntax_attr), syntax_attr.size(), attr);

			/* Merger data and attr together */
			syntax_with_data_and_attr = syntax_with_data + syntax_with_attr;
		}
		
		#ifdef DEBUG
		cout << "SYNTAX IN:\t" << syntax << "[" << attr << "," << data << "]" << endl;
		cout << "SYNTAX OUT:\t" << syntax_with_data_and_attr << endl;
		#endif
	}
	else if (attr_pos == string::npos && data_pos != string::npos){

		cerr << "Syntax:[" << syntax << "] error do not find replaceable attribute!!!" << endl; 
	}
	else if (data_pos == string::npos && attr_pos != string::npos){

		cerr << "Syntax:[" << syntax << "] error do not find replaceable data!!!" << endl; 
	}
	else{

		cerr << "Syntax:[" << syntax << "] error do not find replaceable data and attribute!!!" << endl; 
	}

	
	return syntax_with_data_and_attr;
}


/**************************************************************************************
	@brief	:	Syntax generator, repeate syntax level times, level must less then or
				equal to max_level 
**************************************************************************************/
string Markdown::syntax_generator(const string& syntax, unsigned int level, unsigned int max_level, bool space)
{
	unsigned int idx;
	stringstream format;

	/* Check level */
	if (level > max_level || level == 0){

		cout << "Syntax [" << syntax << "] level range is: 1 - " << max_level << endl; 
		goto out;
	}

	/* Process title level */
	for (idx = 0; idx < level; idx++){

		format << syntax;
	}
	
	/* Append a space at end */
	if (space){

		format << " ";
	}
	
	out:
	return format.str();
}
	

/**************************************************************************************
	@brief	:	Output process
**************************************************************************************/
string Markdown::output_process(const string& context, bool output)
{
	if (md_output.is_open() and output){

		md_output << context << "  " << endl;
	}

	return context;
}


/**************************************************************************************
	@brief	:	Add context with color 
**************************************************************************************/
string Markdown::color_analysis(const string& context, const string& color)
{
	stringstream format;

	/* Color is empty */
	if (color.empty()){
	
		format << context;
	}
	else{

		/* Add color syntax */	
		format.str(syntax_generator(fontcolor_syntax, color, context));
	}

	return format.str();
}


/**************************************************************************************
	@brief	:	Add title
				color_analysic: analysic color with context
				inside syntax_generator: generate title syntax
				outside syntax_generator: generate tile and context with color
**************************************************************************************/
string Markdown::add_title(unsigned int level, const string& title, const string& color)
{
	return output_process(syntax_generator(syntax_generator(title_syntax, level, max_title_level), color_analysis(title, color)));
}

string Markdown::add_h1(const string& title, const string& color)
{
	return add_title(1, title, color);	
}

string Markdown::add_h2(const string& title, const string& color)
{
	return add_title(2, title, color);	
}

string Markdown::add_h3(const string& title, const string& color)
{
	return add_title(3, title, color);	
}

string Markdown::add_h4(const string& title, const string& color)
{
	return add_title(4, title, color);	
}

string Markdown::add_h5(const string& title, const string& color)
{
	return add_title(5, title, color);	
}

string Markdown::add_h6(const string& title, const string& color)
{
	return add_title(6, title, color);	
}


/**************************************************************************************
	@brief	:	Add a horizontal rule
**************************************************************************************/
string Markdown::add_hrule(void)
{
	stringstream format;

	format << endl << hrule_syntax << endl;

	return output_process(format.str());	
}


/**************************************************************************************
	@brief	:	Emphasize, strong, strikethrough, underline, 
**************************************************************************************/
string Markdown::add_emphasize(const string& text)
{
	return output_process(syntax_generator(emphasize_syntax, text));
}

string Markdown::add_strong(const string& text)
{
	return output_process(syntax_generator(strong_syntax, text));	
}

string Markdown::add_strikethrough(const string& text)
{	
	return output_process(syntax_generator(strikethrough_syntax, text));
}

string Markdown::add_underline(const string& text)
{
	return output_process(syntax_generator(underline_syntax, text));
}


/**************************************************************************************
	@brief	:	Superscript and subscript
***************************************************************************************/
string Markdown::add_superscript(const string& text, bool output)
{
	return output_process(syntax_generator(superscript_syntax, text), output);
}

string Markdown::add_subscript(const string& text, bool output)
{
	return output_process(syntax_generator(subscript_syntax, text), output);
}
	

/**************************************************************************************
	@brief	:	Inline code, code block and quoto
**************************************************************************************/
string Markdown::add_code_block(const string &codes)
{
	return output_process(syntax_generator(codeblock_syntax, codes));
}

string Markdown::add_inline_code(const string &codes)
{
	return output_process(syntax_generator(inlinecode_syntax, codes));
}
	
string Markdown::add_quote(const string &quote, const unsigned int level)
{
	return output_process(syntax_generator(syntax_generator(quote_syntax, level, max_quote_level), quote));
}


/**************************************************************************************
	@brief	:	Underordered list and ordered list
**************************************************************************************/
string Markdown::add_ordered_list(const Md_list& list)
{
	stringstream format;
	Md_list::const_iterator it;

	for (it = list.begin(); it != list.end(); it++){

		format << syntax_generator(orderedlist_syntax, int_to_str(it - list.begin() + 1), *it) << endl;
	}

	return output_process(format.str());
}

string Markdown::add_ordered_list(const Md_list& list, unsigned int level)
{
	stringstream format;
	Md_list::const_iterator it;

	for (it = list.begin(); it != list.end(); it++){
		
		format << syntax_generator(syntax_generator(nestedlist_syntax, level, max_nestedlist_level, false), syntax_generator(orderedlist_syntax, int_to_str(it - list.begin() + 1), *it)) << endl;
	}	

	return output_process(format.str());
}

string Markdown::add_ordered_list(unsigned int index, const string& context, unsigned int nested_level)
{
	if (nested_level == 0){
		
		return output_process(syntax_generator(orderedlist_syntax, int_to_str(index), context));
	}
	else{
		return output_process(syntax_generator(syntax_generator(nestedlist_syntax, nested_level, max_nestedlist_level, false), syntax_generator(orderedlist_syntax, int_to_str(index), context)));
	}
}

string Markdown::add_unordered_list(const Md_list& list)
{
	stringstream format;
	Md_list::const_iterator it;

	for (it = list.begin(); it != list.end(); it++){

		format << syntax_generator(unorderedlist_syntax, *it) << endl;
	}

	return output_process(format.str());
}

string Markdown::add_unordered_list(const Md_list& list, unsigned int nested_level)
{
	stringstream format;
	Md_list::const_iterator it;

	for (it = list.begin(); it != list.end(); it++){

		format << syntax_generator(syntax_generator(nestedlist_syntax, nested_level,  max_nestedlist_level, false), syntax_generator(unorderedlist_syntax, *it)) << endl;
	}	

	return output_process(format.str());
}

string Markdown::add_unordered_list(const string& item, unsigned int nested_level)
{
	if (nested_level == 0){
	
		return output_process(syntax_generator(unorderedlist_syntax, item));
	}
	else{
		
		return output_process(syntax_generator(syntax_generator(nestedlist_syntax, nested_level, max_nestedlist_level, false), syntax_generator(unorderedlist_syntax, item)));
	}
}

/**************************************************************************************
	@brief	:	Link, image, anchor, intjump
**************************************************************************************/
string Markdown::add_link(const string& context, const string& link)
{
	return output_process(syntax_generator(link_syntax, link, context));
}

string Markdown::add_image(const string& path, const string& alt_text)
{
	return output_process(syntax_generator(image_syntax, path, alt_text));
}

string Markdown::add_anchor(const string& context, const string& id)
{
	return output_process(syntax_generator(anchor_syntax, id, context));
}

string Markdown::add_intjump(const string& context, const string& id)
{
	return output_process(syntax_generator(intjump_syntax, id, context));
}


/**************************************************************************************
	@brief	:	Add comment
**************************************************************************************/
string Markdown::add_comment(const string& comment)
{
	return output_process(syntax_generator(comment_syntax, comment));
}

/**************************************************************************************
**************************************************************************************/
string Markdown::add_color_start(const string& color)
{
	return output_process(syntax_generator(color_start_syntax, color));
}

string Markdown::add_color_end(void)
{
	return output_process(syntax_generator(color_end_syntax, ""));
}


/**************************************************************************************
	@brief	:	Check if text is a url 
**************************************************************************************/
bool Markdown::is_a_url(const string& text)
{
	Md_list::const_iterator key;

	/* Find link start */
	for (key = link_start.begin(); key != link_start.end(); key++){

		/* At the beging */
		if (text.find(*key) == 0){

			return true;	
		}
	}	

	return false;
}

bool Markdown::is_a_image(const string& text)
{
	Md_list::const_iterator key;

	/* First image link should be a url */
	if (is_a_url(text) == false){

		return false;
	}

	/* Find link end */
	for (key = image_end.begin(); key != image_end.end(); key++){

		if (text.find(*key) + key->size() == text.size()){
		
			return true;
		}
	}

	return false;
}

string Markdown::url_analysis(const string& context, const string& color)
{
	stringstream format;
	string text = context;
	Md_list::const_iterator key;
	string::size_type start, end;
	string url,url_keyword, image_keyword;

	/* Process text, sperate context and url and image */
	for (start = 0, end = 0; text.size(); start = 0, end = 0){

		/* Find if there have url keyword */	
		for (key = link_start.begin(), url_keyword = ""; key != link_start.end(); key++){
		
			/* Found url keyword */
			if ((start = text.find(*key)) != string::npos){

				url_keyword = *key;
				break;
			}
		}

		/* Do not found url */
		if (url_keyword.empty()){

			format << color_analysis(text, color) << endl;
			text.erase(0, text.size());
			continue;
		}


		/* Find if there have image keyword */
		for (key = image_end.begin(), image_keyword = ""; key != image_end.end(); key++){

			/* Found image keyword */
			if ((end = text.find(*key)) != string::npos){

				image_keyword = *key;
				break;
			}
		}

	
		/* Is a normal url */		
		if (image_keyword.empty()){

			/* Context */
			if (start){

				format << color_analysis(text.substr(0, start), color) << endl;
			}

			/* Url */
			url = text.substr(start, text.size());

			/* Remove already processed data */
			format << syntax_generator(link_syntax, url, url) << endl << endl;	
			text.erase(0, text.size());
			continue;	
		}

		/* Is a image url */
		/* Context */
		if (start){

			format << color_analysis(text.substr(0, start), color) << endl;
		}

		/* Url */
		url = text.substr(start, end + image_keyword.size());
		
		/* Remove already processed data */
		format << syntax_generator(image_syntax, url, url) << endl << endl;	
		text.erase(0, start + end + image_keyword.size());
	}
	

	return format.str();
}


/**************************************************************************************
	@brief	:	Add context with color analysic
**************************************************************************************/
string Markdown::add_context(const string& context, const string& color)
{
	Md_list db;
	stringstream format;
	string text = context;
	string::size_type end;	
	Md_list::const_iterator item;

	/* Read context to analysis database */
	while(text.size()){

		/* Find split character */
		end = text.find_first_of(split_ch, 0);			

		/* To the end */
		if (end == string::npos){

			end = text.size();
			db.push_back(text.substr(0, end));
			text.erase(0, end);
		}
		else{
			db.push_back(text.substr(0, end));
			text.erase(0, end + 1);
		}
	}

	/* Process each of the text */
	for (item = db.begin(); item != db.end(); item++){
	
		cout << *item << endl;

		/* Is a image */
		if (is_a_image(*item)){
			
			format << syntax_generator(image_syntax, *item, *item) << endl << endl;
			continue;
		}

		/* Is a link */
		if (is_a_url(*item)){

			format << syntax_generator(link_syntax, *item, *item) << endl;
			continue;
		}
		
		/* Normal context, may be with link or image  */
		format << url_analysis(*item, color);
	}
	
	
	return output_process(format.str());	
}

