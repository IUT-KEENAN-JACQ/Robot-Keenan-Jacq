using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ExtendedSerialPort;

namespace RobotInterface
{
	/// <summary>
	/// Logique d'interaction pour MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();
		}

		private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
		{
			textBoxReception.Text ="Reçu : " + textBoxEmission.Text + "\n" + textBoxReception.Text;
			textBoxEmission.Text = null;

			if (buttonEnvoyer.Background == Brushes.RoyalBlue)
			{
				buttonEnvoyer.Background = Brushes.Beige;
			}
			else
				buttonEnvoyer.Background = Brushes.RoyalBlue;
		}

		private void buttonEnvoyer_KeyUp(object sender, KeyEventArgs e)
		{
			if(e.Key == Key.Enter)
			{

			}

		}
	}
}
