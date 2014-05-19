#include "markdown.h"

int main(int argc, char **argv)
{

	/* Create a markdown file */
	Markdown test("test.md");

	/* Write title 1 */
	test.add_h1("标题1", "red");
	test.add_h2("标题2", "green");
	test.add_h3("标题3", "blue");
	test.add_h4("标题4", "black");
	test.add_h5("标题5", "#00ffff");
	test.add_h6("标题6");

	/* Horizontal line */
	test.add_hrule();


	return 0;
}
