#pragma once

namespace EjemploDataGrid {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//Nuevos namespaces utilizados
	using namespace System::IO;
	

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:




	private: System::Windows::Forms::DataGridView^ dgvMatriz;
	private: System::Windows::Forms::GroupBox^ groupBox1;

	private: System::Windows::Forms::TextBox^ txtPath;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::OpenFileDialog^ ofdImportar;
	private: System::Windows::Forms::SaveFileDialog^ sfdExportar;


	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dgvMatriz = (gcnew System::Windows::Forms::DataGridView());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->txtPath = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->ofdImportar = (gcnew System::Windows::Forms::OpenFileDialog());
			this->sfdExportar = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMatriz))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// dgvMatriz
			// 
			this->dgvMatriz->AllowUserToAddRows = false;
			this->dgvMatriz->AllowUserToDeleteRows = false;
			this->dgvMatriz->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvMatriz->Location = System::Drawing::Point(12, 89);
			this->dgvMatriz->Name = L"dgvMatriz";
			this->dgvMatriz->Size = System::Drawing::Size(670, 368);
			this->dgvMatriz->TabIndex = 5;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->txtPath);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(400, 62);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Importar Datos de Excel";
			// 
			// txtPath
			// 
			this->txtPath->Location = System::Drawing::Point(87, 25);
			this->txtPath->Name = L"txtPath";
			this->txtPath->ReadOnly = true;
			this->txtPath->Size = System::Drawing::Size(263, 20);
			this->txtPath->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(6, 23);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Importar";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// ofdImportar
			// 
			this->ofdImportar->FileName = L"openFileDialog1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(820, 467);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->dgvMatriz);
			this->Name = L"MyForm";
			this->Text = L"Métodos de Ordenamiento";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvMatriz))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private : void ReestablecerMatriz() {
		dgvMatriz->Rows->Clear();
		dgvMatriz->Columns->Clear();
		dgvMatriz->ColumnHeadersVisible = false;
		dgvMatriz->RowHeadersVisible = false;
	};


		   
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

	//Se agregan los filtros al OpenFileDialog
	ofdImportar->Filter = "Archivos separados por coma (csv) | *.csv";
	ofdImportar->FileName = "";	
	
	//Unicamnte si el reultado de la apertura del archivo es exitosa se carga el archivo
	if (ofdImportar->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		ReestablecerMatriz(); //Se elimina cualquier contenido de la matriz
		txtPath->Text = ofdImportar->FileName;

		//Se utiliza el objeto File para leer el archivo solo cuando el FileName es correcto
		//Importante haber llamado al namespace System::IO antes de usar File
		array<String^>^ archivoLineas = File::ReadAllLines(ofdImportar->FileName); 

		if (archivoLineas->Length > 0) {

			//Obtiene la cantidad de elementos de la primer linea y ese toma como cantidad de columnas
			array<String^>^ archivoColumna = archivoLineas[0]->Split(',');
			if (archivoColumna->Length > 0) {
				int cantidadColumnas = archivoColumna->Length;

				//Agrega las columnas
				for (int i = 0; i < cantidadColumnas; i++) {
					//Crea una columna
					DataGridViewColumn^ nuevacolumna = gcnew DataGridViewColumn();
					nuevacolumna->Width = 20;
					//Le agrega el tipo de columna que será
					DataGridViewCell^ cellTemplate = gcnew DataGridViewTextBoxCell();
					nuevacolumna->CellTemplate = cellTemplate;
					//Inserta la columna
					dgvMatriz->Columns->Add(nuevacolumna);
				}

				//Agrega las filas de manera dinámica
				for (int i = 0; i < archivoLineas->Length; i++) {
					dgvMatriz->Rows->Add();
				}

				//Llena el DatagridView
				for (int i = 0; i < archivoLineas->Length; i++) {
					array<String^>^ fila = archivoLineas[i]->Split(',');
					int j = 0;
					
					//Si alguna fila tiene más o menos objetos no afecta al funcionamiento ya que utiliza la cantidad de elementos de la primer fila
					while ((j < cantidadColumnas) && (j < fila->Length)) {
						dgvMatriz->Rows[i]->Cells[j]->Value = fila[j];
						j++;
					}
				}
			}
		}
		
	}
	else {
		// Si no se selecciona correctamente un elemento entonces falla
		MessageBox::Show("No se seleccionó ningún archivo"
			, "Archivo no seleccionado"
			, MessageBoxButtons::OK
			, MessageBoxIcon::Exclamation);
	}
}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
