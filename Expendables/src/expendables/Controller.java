/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

public class Controller {
	private Model model;

	public void setNickname(String s) {
		model.setName(s);
	}

	public void buyUnit(String s) {
		model.buyUnit(s);
	}

	Controller(Model model) {
		this.model = model;
	}

}
