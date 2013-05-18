/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.Insets;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JToggleButton;
import javax.swing.SwingConstants;

/**
 * 
 * @author vkalit-lenovo
 */
public class MyJPanel extends JPanel {

	ImagePanel m_pp;
	private Image image;
	Model model;
	Controller controller;

	// private List<List<Integer>> list = new ArrayList<List<Integer>>();

	MyJPanel(Model m, Controller c, ImagePanel pp) {
		this.model = m;
		this.controller = c;
		m_pp = pp;
		add(m_pp);

	}

	protected void paintComponent() {

		// super.paintComponent(g);
		/*
		 * //g.drawImage(image, 0, 0, getWidth(), getHeight(), null); this.g =
		 * g; for (int i = 0; i <= 800; i += 40) { g.drawLine(i, 0, i, 600); }
		 * for (int j = 0; j <= 600; j += 40) { g.drawLine(0, j, 800, j); }
		 */

		/*
		 * for (Unit unit : model.player1.army){ String s1 =
		 * String.valueOf(unit.x); String s2 = String.valueOf(unit.y);
		 * 
		 * System.out.print("x,y = " +s1 + "," + s2 + ".   "); }
		 */

		for (Unit unit : model.player1.army) {
			try {
				paint(unit.x, unit.y, unit, true);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		for (Unit unit : model.player2.army) {
			try {
				paint(unit.x, unit.y, unit, false);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}

	public void setImage(Image image) {
		this.image = image;
	}

	public void paint( final int x, final int y, Unit u, boolean first) throws IOException {// throws IOException{
		setLayout(null);

		  JToggleButton button2=new JToggleButton();

		  ImageIcon icon = null;
		if (u instanceof Swordsman){
			if (first) {
				if (u == model.currUnit(model.cur)) {
					icon = new ImageIcon("sw1_w.jpg");
				} else {
					icon = new ImageIcon("sw1.jpg");
				}
			} else {
				if (u == model.currUnit(model.cur)) {
					icon = new ImageIcon("sw2_w.jpg");
				} else {
					icon = new ImageIcon("sw2.jpg");
				}
			}
		} else if (u instanceof Pikeman) {
			if (first) {
				if (u == model.currUnit(model.cur)) {
					icon = new ImageIcon("pm1_w.jpg");
				} else {
					icon = new ImageIcon("pm1.jpg");
				}
			} else {
				if (u == model.currUnit(model.cur)) {
					icon = new ImageIcon("pm2_w.jpg");
				} else {
					icon = new ImageIcon("pm2.jpg");
				}
			}	
		} else if (u instanceof Archer) {
			if (first) {
				if (u == model.currUnit(model.cur)) {
					icon = new ImageIcon("ar1_w.jpg");
				} else {
					icon = new ImageIcon("ar1.jpg");
				}
			} else {
				if (u == model.currUnit(model.cur)) {
					icon = new ImageIcon("ar2_w.jpg");
				} else {
					icon = new ImageIcon("ar2.jpg");
				}
			}	
		} else if (u instanceof Knight) {
			if (first) {
				if (u == model.currUnit(model.cur)) {
					icon = new ImageIcon("kn1_w.jpg");
				} else {
					icon = new ImageIcon("kn1.jpg");
				}
			} else {
				if (u == model.currUnit(model.cur)) {
					icon = new ImageIcon("kn2_w.jpg");
				} else {
					icon = new ImageIcon("kn2.jpg");
				}
			}
		}
		
button2.setSelected(true);
		button2.setSize(39, 39);
		button2.setPreferredSize(new Dimension(39, 39));
		button2.setLocation(1+x, 1+y);
		JLabel label2= makeLabel(String.valueOf(u.Health) + "   ",JLabel.CENTER, JLabel.CENTER, icon);

		  button2.setLayout(new BorderLayout());
		  button2.add(label2);
			button2.setMargin(new Insets(0,0,0,0));
		
			button2.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent evt) {
				
				goTo();
				evt.getLocationOnScreen();
				int xx = evt.getX()+x;
				int yy = evt.getY()+y;
				
				
				
				
				System.out.print("(" + xx + "," + yy + ")");


				
			}
		});

		m_pp.add(button2);


		thisLink().setVisible(true);
	}

	protected static JLabel makeLabel(String s, int vert, int horiz, Icon icon) {
		JLabel l = new JLabel(s, icon, SwingConstants.CENTER);
		l.setFont(new java.awt.Font("Tahoma", 1, 15));
		l.setVerticalTextPosition(vert);
		l.setHorizontalTextPosition(horiz);
		return l;
	}

	public void goTo() {
		this.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent evt) {

				evt.getLocationOnScreen();
				int xx = evt.getX();
				int yy = evt.getY();

				int cx = model.currUnit(model.cur).x;
				int cy = model.currUnit(model.cur).y;

				
				
					
				if (((xx > cx) && (xx < cx + 40) && (yy > cy + 40) && (yy < cy + 80)) || ((xx > cx) && (xx < cx + 40) && (yy < cy)
						&& (yy > cy - 40)) || ((xx < cx) && (xx > cx - 40) && (yy > cy)
								&& (yy < cy + 40))||((xx > cx + 40) && (xx < cx + 80) && (yy > cy)
										&& (yy < cy + 40))){
				
					
					if (!(model.currUnit(model.cur) instanceof Knight)) {
					
					int i = model.cur.army.indexOf(model.currUnit(model.cur));

						if ((xx > cx) && (xx < cx + 40) && (yy > cy + 40)
								&& (yy < cy + 80)) {
							if (model.isEnemy(model.cur, cx, cy+40)){
								model.fight (model.currUnit(model.cur),model.unitEnemy(model.cur, cx, cy+40));

							} else {
								model.setCurrUnit(cx, cy + 40);
								model.cur.army.remove(i);
								model.cur.army.add(i, model.currUnit(model.cur));
							}
						} else if ((xx > cx) && (xx < cx + 40) && (yy < cy)
								&& (yy > cy - 40)) {
							if (model.isEnemy(model.cur, cx, cy - 40)){
								model.fight (model.currUnit(model.cur),model.unitEnemy(model.cur,cx, cy - 40));

							} else {
								model.setCurrUnit(cx, cy - 40);
								model.cur.army.remove(i);
								model.cur.army.add(i, model.currUnit(model.cur));
							}
						} else if ((xx < cx) && (xx > cx - 40) && (yy > cy)
								&& (yy < cy + 40)) {
							if (model.isEnemy(model.cur, cx - 40, cy)){
								model.fight (model.currUnit(model.cur),model.unitEnemy(model.cur, cx - 40, cy));

							} else {
								model.setCurrUnit(cx - 40, cy);
								model.cur.army.remove(i);
								model.cur.army.add(i, model.currUnit(model.cur));
							}
						} else if ((xx > cx + 40) && (xx < cx + 80) && (yy > cy)
								&& (yy < cy + 40)) {
							if (model.isEnemy(model.cur, cx + 40, cy)){
								model.fight (model.currUnit(model.cur),model.unitEnemy(model.cur, cx + 40, cy));

							} else {
								model.setCurrUnit(cx + 40, cy);
								model.cur.army.remove(i);
								model.cur.army.add(i, model.currUnit(model.cur));
							}
						}
				
					
					
						model.currUnitUp(model.cur);
						if (model.cur == model.player1) {
							model.cur = model.player2;
						} else {
							model.cur = model.player1;
						}
		
						m_pp.removeAll();
						paintComponent();
						m_pp.repaint();
						m_pp.repaint();
						m_pp.revalidate();
					
					
					}
					}
					
					
					
					
					
					
					
					if ( (model.currUnit(model.cur) instanceof Knight) && ( 
							  ((xx >cx -40) && (xx < cx+80)  && (yy >cy -40) && (yy <cy+ 80))
							||((xx >cx -80) && (xx <cx+ 120) && (yy >cy )    && (yy <cy+ 40))
							||((xx > cx)    && (xx < cx+40)  && (yy >cy -80) && (yy <cy+ 120))     )
							
							
					
							
							){
						System.out.print("!_!_!_!");
						
						int i = model.cur.army.indexOf(model.currUnit(model.cur));
						if        ((xx > cx)      && (xx < cx + 40) && (yy > cy + 40) && (yy < cy + 80)) {
							
							model.setCurrUnit(cx, cy + 40);
						} else if ((xx > cx)      && (xx < cx + 40) && (yy < cy)      && (yy > cy - 40)) {
							
							model.setCurrUnit(cx, cy - 40);
						} else if ((xx < cx)      && (xx > cx - 40) && (yy > cy)      && (yy < cy + 40)) {
							
							model.setCurrUnit(cx - 40, cy);
						} else if ((xx > cx + 40) && (xx < cx + 80) && (yy > cy)      && (yy < cy + 40)) {
							
							model.setCurrUnit(cx + 40, cy);
						} else if ((xx > cx + 40) && (xx < cx + 80) && (yy > cy + 40) && (yy < cy + 80)) {
							
							model.setCurrUnit(cx + 40, cy + 40);
						} else if ((xx > cx + 40) && (xx < cx + 80) && (yy > cy - 40) && (yy < cy ))     {
							
							model.setCurrUnit(cx + 40, cy - 40);
						} else if ((xx > cx - 40) && (xx < cx ) && (yy > cy - 40)      && (yy < cy)) {
							
							model.setCurrUnit(cx - 40, cy -40);
						} else if ((xx > cx - 40) && (xx < cx ) && (yy > cy + 40)      && (yy < cy + 80)) {
							
							model.setCurrUnit(cx - 40, cy + 40);
						} else if ((xx > cx ) && (xx < cx + 40) && (yy > cy - 80)	  && (yy < cy - 40)) {
							
							model.setCurrUnit(cx , cy-80);
						} else if ((xx > cx ) && (xx < cx + 40) && (yy > cy + 80)      && (yy < cy + 120)) {
							
							model.setCurrUnit(cx , cy+80);
						} else if ((xx > cx + 80) && (xx < cx + 120) && (yy > cy)      && (yy < cy + 40)) {
							
							model.setCurrUnit(cx + 80, cy);
						} else if ((xx > cx - 80) && (xx < cx - 40) && (yy > cy)      && (yy < cy + 40)) {
							
							model.setCurrUnit(cx - 80, cy);
						}						
						model.cur.army.remove(i);
						model.cur.army.add(i, model.currUnit(model.cur));	
						
					model.currUnitUp(model.cur);
					if (model.cur == model.player1) {
						model.cur = model.player2;
					} else {
						model.cur = model.player1;
					}
	
					m_pp.removeAll();
					paintComponent();
					m_pp.repaint();
					m_pp.repaint();
					m_pp.revalidate();
				}
			}
		});
	}

	private MyJPanel thisLink() {
		return this;
	}

}