powerELEMENT(char *gmadFile, char *rootFile)
{
	gStyle->SetOptTitle(0);
	BDSCanvas *b = new BDSCanvas(gmadFile);
   TFile *f = TFile::Open(rootFile);
	TNtuple *ntuple = (TNtuple*)f->Get("ElossNtuple");
	Int_t i=1,n=1;
	Double_t coeff = 0.061;
	char temp[256];
	TH1F *myhisto= new TH1F("myhisto","Histo from the ntuple projection",
	b->GetNumberElement(),b->GetTableElement());
	sprintf(temp,"E*%lf",coeff);
	ntuple->Project("myhisto","z",temp);
	for(Int_t i=1;i<b->GetNumberElement();i++) 
	 cout << b->GetNameElement()[i] << " " << i << " " << b->GetTableElement()[i] <<"  " << 
	 myhisto->GetBinContent(i)<< endl;   
	
	for(Int_t i=1;i<b->GetNumberElement();i++)
	{
	myhisto->SetBinContent(i,myhisto->GetBinContent(i)/(b->GetTableElement()[i]-b->GetTableElement()[i-1]));
	//cout << b->GetNameElement()[i]  << " " 
	//++<< (b->GetTableElement()[i]-b->GetTableElement()[i-1]) << " " 
	//<< myhisto->GetBinContent(i)   << " "  
	//<<myhisto->GetBinContent(i)/(b->GetTableElement()[i]-b->GetTableElement()[i-1]) << endl;
	}
	
//for(Int_t i=1;i<b->GetNumberElement();i++) 
//	cout << b->GetNameElement()[i] << " " << i << " " << b->GetTableElement()[i] <<"  " << 
//	myhisto->GetBinContent(i)<< endl;	
	//myhisto->GetXaxis()->SetLimits(BDSPad::xmin_axis,BDSPad::xmax_axis);
	myhisto->Draw();
	b->SetHisto(myhisto);
	b->cd();
}

