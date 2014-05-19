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
const string Markdown::underline_syntax	 	= 	"<s>data<s>";
const string Markdown::strikethrough_syntax	=	"<u>data</u>";
const string Markdown::superscript_syntax	=	"<sup>data</sup>";
const string Markdown::subscript_syntax		=	"<sub>data</sub>";
const string Markdown::code_syntax			= 	"<p><code>data</code></p>";
const string Markdown::inlinecode_syntax	=	"`rep`";	
const string Markdown::quote_syntax			= 	"> ";
const string Markdown::comment_syntax		=	"";
const string Markdown::unorderedlist_syntax	=	"+ ";
const string Markdown::fontcolor_syntax		=	"<font color=attr>data</font>";
const string Markdown::link_syntax			=	"[data](http://attr)";
const string Markdown::image_syntax			=	"![data](attr)";
const string Markdown::anchor_syntax		=	"<a id=\"attr\">data</a>";
const string Markdown::intjump_syntax		=	"[data[#attr]";


/**************************************************************************************
	@brief	:	Syntax replace function 
**************************************************************************************/
string Markdown::syntax_generator(const string& syntax, const string& data)
{
	string syntax_with_data = syntax;	

	/* Check syntax */
	if (syntax.find(syntax_data) != string::npos){

		/* Into data to syntax */
		syntax_with_data.replace(syntax.find_first_of(syntax_data), syntax_data.size(), data);
	}
	else{

		cerr << "Syntax:[" << syntax << "] error do not find replaceable data!!!" << endl; 
	}

	return syntax_with_data;
}

string Markdown::syntax_generator(const string& syntax, const string& attr, const string& data)
{
	string::size_type attr_pos, data_pos;
	string syntax_with_data, syntax_with_attr;
	string syntax_with_data_and_attr = syntax;

	/* Get attribute and data postion */
	attr_pos = syntax.find(syntax_attr);
	data_pos = syntax.find(syntax_data);

	cout << attr_pos << "," << data_pos << endl;

	/* Check syntax */
	if (attr_pos != string::npos && data_pos != string::npos){

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
	@brief	:	Constructor and destructor
**************************************************************************************/
Markdown::Markdown(const string& filename)
{
	string output_name = filename;

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
	@brief	:	Output process
**************************************************************************************/
string Markdown::output_process(const string& context)
{
	if (md_output.is_open()){

		md_output << context << endl;
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
	
		format << " " << context << endl;		
	}
	else{

		/* Add color syntax */	
		format << " <font color=" << color << ">" << context << "</font>" << endl;
	}

	//cout << syntax_generator(fontcolor_syntax, "red", "hello") << endl;
	//cout << syntax_generator(link_syntax, "red", "hello") << endl;

	return format.str();
}


/**************************************************************************************
	@brief	:	Add title
**************************************************************************************/
string Markdown::add_title(unsigned int level, const string& title, const string& color)
{
	unsigned int idx;
	stringstream format;
	
	/* Check level */
	if (level > 6){

		goto out;
	}

	/* Process title level */	
	for (idx = 0; idx < level; idx++){

		format << title_syntax;
	}

	/* Process title text */
	format << color_analysis(title, color);

	out:
	return output_process(format.str());	
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

	format << hrule_syntax << endl;

	return output_process(format.str());	
}

/**************************************************************************************
	@brief	:	Add context with color analysic
**************************************************************************************/
string Markdown::add_context(const string& context, const string& color)
{
	stringstream format;

	return output_process(format.str());	
}



