namespace WarePro_ControlApplication
{
    public partial class ControlApplication : System.Windows.Forms.Form
    {
        NetworkManager networkManager;

        public ControlApplication()
        {
            InitializeComponent();
            // Fill the combobox with the shelves
            foreach (Shelves shelf in Enum.GetValues(typeof(Shelves)))
            {
                cbShelves.Items.Add(shelf);
            }
        }
        private async void ControlApplication_Load(object sender, EventArgs e)
        {
            networkManager = new NetworkManager();

            string ipport = await networkManager.StartServer();
            lbLogs.Items.Add(ipport);
            while (true)
            {
                // Read data from the stream (this is a blocking call)
                string incommingmsg = await networkManager.ReadData();
                lbLogs.Items.Add(incommingmsg);
            }

        }


        private void btnSendTestMsg_Click(object sender, EventArgs e)
        {
            string message = tbTestMessage.Text;
            networkManager.WriteData(message);
        }

        private void btnGoToLocation_Click(object sender, EventArgs e)
        {
            string location = cbShelves.SelectedItem.ToString();
            networkManager.WriteData($"$MOVE{location};");
        }

        private void btnGoToRestLocation_Click(object sender, EventArgs e)
        {
            networkManager.WriteData("$MOVEXX;"); // Move to the rest location
        }
    }
}
