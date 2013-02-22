/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JPanel;


public class ForsesOverview extends JFrame {

	JPanel pane = new JPanel();
	Model model;
	Controller controller;

	private void initComponents() throws IOException {

		this.setIconImage(ImageIO.read(new File("icon.jpg")));
		this.setResizable(false);
		this.setSize(800, 600);
		this.setBackground(Color.GRAY);

		jLabel1 = new javax.swing.JLabel();
		jLabel2 = new javax.swing.JLabel();
		jLabel3 = new javax.swing.JLabel();
		jLabel4 = new javax.swing.JLabel();
		jLabel5 = new javax.swing.JLabel();
		jLabel6 = new javax.swing.JLabel();
		jLabel7 = new javax.swing.JLabel();
		jLabel8 = new javax.swing.JLabel();
		jLabel9 = new javax.swing.JLabel();
		jLabel10 = new javax.swing.JLabel();
		jButton1 = new javax.swing.JButton();

		ImagePanel pp = new ImagePanel();
		try {
			pp.setImage(ImageIO.read(new File("Expendables_fight.jpg")));
		} catch (IOException e) {
			e.printStackTrace();
		}

		pane.setBackground(Color.GRAY);
		pane.setSize(800, 600);
		pane.setOpaque(false);

		// pane.add(goldValue);

		// pp.add(pane, java.awt.BorderLayout.CENTER);
		// pp.setBackground(Color.GRAY);
		// pp.setPreferredSize(new Dimension(800, 600));

		jLabel1.setFont(new java.awt.Font("Tahoma", 1, 40));
		jLabel1.setText(model.player2.name);

		jLabel2.setFont(new java.awt.Font("Tahoma", 1, 40));
		jLabel2.setText(model.player1.name);

		jLabel3.setFont(new java.awt.Font("Tahoma", 1, 30));
		jLabel3.setText(String.valueOf("Swordsman: "
				+ model.player1.getSwordsman()));

		jLabel4.setFont(new java.awt.Font("Tahoma", 1, 30));
		jLabel4.setText(String.valueOf("Pikeman: " + model.player1.getPikeman()));

		jLabel5.setFont(new java.awt.Font("Tahoma", 1, 30));
		jLabel5.setText(String.valueOf("Archer: " + model.player1.getArcher()));

		jLabel6.setFont(new java.awt.Font("Tahoma", 1, 30));
		jLabel6.setText(String.valueOf("Knight: " + model.player1.getKnight()));

		jLabel7.setFont(new java.awt.Font("Tahoma", 1, 30));
		jLabel7.setText(String.valueOf("Swordsman: "
				+ model.player2.getSwordsman()));

		jLabel8.setFont(new java.awt.Font("Tahoma", 1, 30));
		jLabel8.setText(String.valueOf("Pikeman: " + model.player2.getPikeman()));

		jLabel9.setFont(new java.awt.Font("Tahoma", 1, 30));
		jLabel9.setText(String.valueOf("Archer: " + model.player2.getArcher()));

		jLabel10.setFont(new java.awt.Font("Tahoma", 1, 30));
		jLabel10.setText(String.valueOf("Knight: " + model.player2.getKnight()));

		jButton1.setText("Fight!");
		jButton1.setFont(new java.awt.Font("Tahoma", 1, 50));
		jButton1.setOpaque(true);
		jButton1.setContentAreaFilled(true);
		jButton1.setBackground(Color.GRAY);

		javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(
				pane);
		pane.setLayout(jPanel1Layout);
		jPanel1Layout
				.setHorizontalGroup(jPanel1Layout
						.createParallelGroup(
								javax.swing.GroupLayout.Alignment.LEADING)
						.addGroup(
								jPanel1Layout
										.createSequentialGroup()
										.addGap(35, 35, 35)
										.addGroup(
												jPanel1Layout
														.createParallelGroup(
																javax.swing.GroupLayout.Alignment.LEADING,
																false)
														.addComponent(
																jLabel3,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																254,
																Short.MAX_VALUE)
														.addComponent(
																jLabel2,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE)
														.addComponent(
																jLabel4,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE)
														.addComponent(
																jLabel5,
																javax.swing.GroupLayout.Alignment.TRAILING,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE)
														.addComponent(
																jLabel6,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE))
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED,
												javax.swing.GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE)
										.addGroup(
												jPanel1Layout
														.createParallelGroup(
																javax.swing.GroupLayout.Alignment.LEADING,
																false)
														.addComponent(
																jLabel1,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																254,
																Short.MAX_VALUE)
														.addComponent(
																jLabel7,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE)
														.addComponent(
																jLabel8,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE)
														.addComponent(
																jLabel9,
																javax.swing.GroupLayout.Alignment.TRAILING,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE)
														.addComponent(
																jLabel10,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE))
										.addGap(44, 44, 44))
						.addGroup(
								javax.swing.GroupLayout.Alignment.TRAILING,
								jPanel1Layout
										.createSequentialGroup()
										.addContainerGap(339, Short.MAX_VALUE)
										.addComponent(
												jButton1,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												200,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addGap(301, 301, 301)));
		jPanel1Layout
				.setVerticalGroup(jPanel1Layout
						.createParallelGroup(
								javax.swing.GroupLayout.Alignment.LEADING)
						.addGroup(
								jPanel1Layout
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												jPanel1Layout
														.createParallelGroup(
																javax.swing.GroupLayout.Alignment.LEADING)
														.addComponent(
																jLabel2,
																javax.swing.GroupLayout.PREFERRED_SIZE,
																70,
																javax.swing.GroupLayout.PREFERRED_SIZE)
														.addComponent(
																jLabel1,
																javax.swing.GroupLayout.PREFERRED_SIZE,
																65,
																javax.swing.GroupLayout.PREFERRED_SIZE))
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addGroup(
												jPanel1Layout
														.createParallelGroup(
																javax.swing.GroupLayout.Alignment.LEADING,
																false)
														.addComponent(
																jLabel3,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																38,
																Short.MAX_VALUE)
														.addComponent(
																jLabel8,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE))
										.addGap(11, 11, 11)
										.addGroup(
												jPanel1Layout
														.createParallelGroup(
																javax.swing.GroupLayout.Alignment.BASELINE)
														.addComponent(
																jLabel4,
																javax.swing.GroupLayout.PREFERRED_SIZE,
																38,
																javax.swing.GroupLayout.PREFERRED_SIZE)
														.addComponent(
																jLabel7,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE))
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
										.addGroup(
												jPanel1Layout
														.createParallelGroup(
																javax.swing.GroupLayout.Alignment.BASELINE)
														.addComponent(
																jLabel5,
																javax.swing.GroupLayout.PREFERRED_SIZE,
																38,
																javax.swing.GroupLayout.PREFERRED_SIZE)
														.addComponent(
																jLabel9,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE))
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
										.addGroup(
												jPanel1Layout
														.createParallelGroup(
																javax.swing.GroupLayout.Alignment.BASELINE)
														.addComponent(
																jLabel6,
																javax.swing.GroupLayout.PREFERRED_SIZE,
																38,
																javax.swing.GroupLayout.PREFERRED_SIZE)
														.addComponent(jLabel10))
										.addPreferredGap(
												javax.swing.LayoutStyle.ComponentPlacement.RELATED,
												182, Short.MAX_VALUE)
										.addComponent(
												jButton1,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												57,
												javax.swing.GroupLayout.PREFERRED_SIZE)
										.addGap(89, 89, 89)));

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(pp);
		pp.setLayout(layout);
		layout.setHorizontalGroup(layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addComponent(pane,
				javax.swing.GroupLayout.DEFAULT_SIZE,
				javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));
		layout.setVerticalGroup(layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addComponent(pane,
				javax.swing.GroupLayout.DEFAULT_SIZE,
				javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));

		jButton1.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent evt) {
				setVisibleFalse();

				Field f = null;
				try {
					f = new Field(controller, model);
				} catch (IOException ex) {
					Logger.getLogger(ForsesOverview.class.getName()).log(
							Level.SEVERE, null, ex);
				}
				f.setVisible(true);

			}
		});

		pane.setVisible(true);

		pp.add(pane, java.awt.BorderLayout.CENTER);
		pp.setBackground(Color.GRAY);
		pp.setPreferredSize(new Dimension(800, 600));

		this.add(pp, java.awt.BorderLayout.CENTER);
		this.pack();
		this.setLocationRelativeTo(null);
	}

	private void setVisibleFalse() {
		this.setVisible(false);
	}

	ForsesOverview(Controller c, Model m) throws IOException {
		controller = c;
		model = m;
		initComponents();
	}

	private javax.swing.JButton jButton1;
	private javax.swing.JFrame jFrame1;
	private javax.swing.JLabel jLabel1;
	private javax.swing.JLabel jLabel10;
	private javax.swing.JLabel jLabel2;
	private javax.swing.JLabel jLabel3;
	private javax.swing.JLabel jLabel4;
	private javax.swing.JLabel jLabel5;
	private javax.swing.JLabel jLabel6;
	private javax.swing.JLabel jLabel7;
	private javax.swing.JLabel jLabel8;
	private javax.swing.JLabel jLabel9;
	private javax.swing.JPanel jPanel1;
}
