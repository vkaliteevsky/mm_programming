/**
 * @author vkaliteevskiy
 * GUI
 * (c)2012
 */

package expendables;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.IOException;
import java.util.Locale;
import java.util.Observable;
import java.util.Observer;
import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 * 
 * @author vkaliteevskiy
 */
public class Initialization extends JDialog implements ActionListener {
	private JTextField nicknameField;
	private Model model = new Model();

	// private Controller controller = new Controller(model);

	Initialization(final NewGame f) throws IOException {
		super(f);
		final JTextField nicknameField = new javax.swing.JTextField();
		label1 = new JLabel();
		jButton1 = new javax.swing.JButton();

		this.setIconImage(ImageIO.read(new File("icon.jpg")));
		this.setResizable(false);
		this.setSize(456, 309);
		// this.setBackground(Color.GRAY);

		ImagePanel pp = new ImagePanel();
		try {
			pp.setImage(ImageIO.read(new File("Expendables_name.jpg")));
		} catch (IOException e) {
			e.printStackTrace();
		}

		JPanel pane = new JPanel();

		pane.setBackground(Color.GRAY);
		pane.setSize(456, 309);
		pane.setOpaque(false);
		pp.add(pane, java.awt.BorderLayout.CENTER);
		// pp.setBackground(Color.GRAY);
		pp.setPreferredSize(new Dimension(456, 309));

		label1.setOpaque(false);
		label1.setText("Nickname:");
		label1.setFont(new java.awt.Font("Tahoma", 1, 25));

		nicknameField.setText("");
		nicknameField.setLocale(Locale.UK);
		nicknameField.setFont(new java.awt.Font("Tahoma", 1, 20));

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(pane);
		pane.setLayout(layout);
		layout.setHorizontalGroup(layout
				.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
				.addGroup(
						layout.createSequentialGroup()
								.addGap(143, 143, 143)
								.addGroup(
										layout.createParallelGroup(
												javax.swing.GroupLayout.Alignment.LEADING,
												false)
												.addComponent(
														label1,
														javax.swing.GroupLayout.DEFAULT_SIZE,
														javax.swing.GroupLayout.DEFAULT_SIZE,
														Short.MAX_VALUE)
												.addComponent(
														nicknameField,
														javax.swing.GroupLayout.DEFAULT_SIZE,
														180, Short.MAX_VALUE)
												.addComponent(
														jButton1,
														javax.swing.GroupLayout.Alignment.TRAILING,
														javax.swing.GroupLayout.PREFERRED_SIZE,
														119,
														javax.swing.GroupLayout.PREFERRED_SIZE))
								.addContainerGap(133, Short.MAX_VALUE)));
		layout.setVerticalGroup(layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addGroup(
				layout.createSequentialGroup()
						.addGap(29, 29, 29)
						.addComponent(label1,
								javax.swing.GroupLayout.PREFERRED_SIZE, 79,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addGap(22, 22, 22)
						.addComponent(nicknameField,
								javax.swing.GroupLayout.PREFERRED_SIZE, 54,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addGap(18, 18, 18)
						.addComponent(jButton1,
								javax.swing.GroupLayout.PREFERRED_SIZE, 38,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addContainerGap(69, Short.MAX_VALUE)));

		pack();

		jButton1.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent evt) {
				String nick = nicknameField.getText();
				f.setName(nick);
				f.setPaneVisibleFalse();
				setVisibleFalse();
				// controller.setNickname(nick);
			}
		});

		jButton1.setText("Next");

		this.add(pp, java.awt.BorderLayout.CENTER);
		this.pack();
		this.setLocationRelativeTo(null);
	}

	private void setVisibleFalse() {
		setVisible(false);
	}



	private JLabel label1;
	private JButton jButton1;

	@Override
	public void actionPerformed(ActionEvent e) {

	}

}
