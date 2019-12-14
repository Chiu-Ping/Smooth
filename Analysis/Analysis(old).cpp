#include "Channel.hpp"
#include "Event.hpp"
#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH1F.h"
#include <vector>
#include "TTreeReader.h"
#include "TSpectrum.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TAxis.h"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{ 	
//		TFile fileIn(("/home/shenqiuping/RPC_Anal/data/Run_"+std::to_string(run)+".root").c_str());
	TString Num_data;
	
	std::cout << argc <<" " << argv[0] << " " << argv[1] << std::endl; 
	if( argc<0 || argc>3)
    {
		std::cout << "It NEED only one string pararemeter for the data NAME!" << std::endl; 
		exit(-5);  
	}
  	else 
    	Num_data = std::string(argv[1]);

	//TFile fileIn("/home/shenqiuping/RPC_Anal/data/New_Data/Run_"+Num_data+".root");
	TFile fileIn("/home/shenqiuping/RPC_Anal/data/Run_"+Num_data+".root");
	if (fileIn.IsZombie()) 
	{
  		std::cout << "Error opening file: Run_" << Num_data << ".root file doesn't exsist!" << std::endl;
		exit(-1);
	}
	std::ofstream Eff_file;
	std::ofstream out("./Procees_content.txt");
	std::ofstream log("./Run_"+Num_data+".txt");
	std::ofstream ratiof("../Ratio_4.txt");
	std::ofstream ratiow("../Ratio_5.txt");
	
/*****************************Code for inputing the signal samples****************************/
	Int_t Signal_info[2][9999]={0},Nsig=0;
	std::ifstream infile;
	infile.open("/home/shenqiuping/RPC_Anal/Smooth/Run62/Signal.txt");
	if (!infile.is_open()) exit (EXIT_FAILURE);
	
	for(Int_t i=0;!infile.eof();i++)
	{
		infile >> Signal_info[0][i] >> Signal_info[1][i];
	//	std::cout << Signal_info[0][i] << "\t" << Signal_info[1][i] << std::endl;
		Nsig++;
	}
	infile.close();

/****************************Code for processing data******************************************/
/***********************define many variables*******************************/
   	TTree *t1 = (TTree*)fileIn.Get("Tree");
   	Event* event{nullptr};
   	t1->SetBranchAddress("Events",&event);
	TCanvas *c_sigma = new TCanvas("c_sigma","",600,600);
	TCanvas *c_SNR = new TCanvas("c_SNR","",600,600);
    TCanvas *c_SN_sjtu = new TCanvas("c_SN_sjtu","RPC Sig & Bkg",600,600);
    TCanvas *c_SN_ustc = new TCanvas("c_SN_ustc","RPC Sig & Bkg",600,600);
   
   	Double_t Eff[32]={0};
   	Int_t Nsig_SJTUf=0,Nsig_USTCf=0,Nsig_SJTUw=0,Nsig_USTCw=0;
    Int_t Nsig_SJTU_Tot=0,Nsig_USTC_Tot=0,Nbkg_Tot_u=0,Nbkg_Tot_s=0,
			Nbkg_sig_uf=0,Nbkg_sig_sf=0,
			Nbkg_sig_uw=0,Nbkg_sig_sw=0; 
   
   	TH1F *Hist_SigmaCh[32]; 
    TH1F *Hist_SN_Ratio_ChP[32];  
    TH1F *Hist_SN_Ratio_ChN[32];  
    
	TH1F *Hist_SN_Ratio_sjtu = new TH1F("Hist_SN_Ratio_sjtu","",30,-0.01,15); 
    TH1F *Hist_BG_Ratio_sjtu = new TH1F("Hist_BG_Ratio_sjtu","",30,-0.01,15);
    TH1F *Hist_SN_Ratio_ustc = new TH1F("Hist_SN_Ratio_ustc","",30,-0.01,15); 
    TH1F *Hist_BG_Ratio_ustc = new TH1F("Hist_BG_Ratio_ustc","",30,-0.01,15);

	Double_t Hist_bin[999999];	
	//read all entries and fill the histogram
    Double_t Nsig_neg_Ch[32]={0},Nsig_pos_Ch[32]={0};

    for(int channel=0; channel!=18;++channel)
	{ 
		if(channel>=0 && channel<=7 )
			Hist_SigmaCh[channel]= new TH1F(("Hist_SigmaCh"+std::to_string(channel)).c_str(),"",50,0,0.01);
		
		else if(channel==9 || channel>10 && channel<=12 || channel==16)
			Hist_SigmaCh[channel]= new TH1F(("Hist_SigmaCh"+std::to_string(channel)).c_str(),"",50,0,0.0009);
		
		else if(channel==8 || channel ==17) 
			Hist_SigmaCh[channel]= new TH1F(("Hist_SigmaCh"+std::to_string(channel)).c_str(),"",50,0,0.125);
		
		else if(channel==10)
			Hist_SigmaCh[channel]= new TH1F(("Hist_SigmaCh"+std::to_string(channel)).c_str(),"",50,0,0.0014);
		
		else  
			Hist_SigmaCh[channel]= new TH1F(("Hist_SigmaCh"+std::to_string(channel)).c_str(),"",50,0,0.012);
		
		Hist_SN_Ratio_ChP[channel]= new TH1F(("Hist_SN_Ratio_Ch"+std::to_string(channel)+"P").c_str(),"",60,0,10);
		Hist_SN_Ratio_ChN[channel]= new TH1F(("Hist_SN_Ratio_Ch"+std::to_string(channel)+"N").c_str(),"",60,0,10);
	} 
   
   Long64_t nentries = t1->GetEntries(); 
   std::cout<< "Total events:"<< nentries << std::endl;
   
   for (Long64_t i=0;i<nentries;i++) 
   {	
   	 if(i<=300)
	 {	 		 
	 Bool_t NegSig_Truth[32];

			t1->GetEntry(i);
     		log <<event->EventNumber<<  //std::endl;
     		 "**********************************************************" << std::endl; 
	for(unsigned int channel=0;channel!=18;++channel)
     {
        double min{999999};
        double max{-99999};
		double Mean[1024],Sum=0,Max_mean=0,Min_mean=10,Sigma_y=0,Sigma2=0;
        double NbrTicks=event->Channels[channel].Data.size();
        double MaxTime=event->Channels[channel].Time[NbrTicks-1];
  
        TCanvas can;
        TH1F *test = new TH1F("Test","Test",NbrTicks,0,NbrTicks);
        TH1F *smooth = new TH1F("Smooth","Smooth",NbrTicks,0,NbrTicks);  //adding the raw smooth      

        for(unsigned int j=0;j!=event->Channels[channel].Data.size();++j)
        {
            if(event->Channels[channel].Data[j]*1.0/4096<min)min=event->Channels[channel].Data[j]*1.0/4096;
            else if (event->Channels[channel].Data[j]*1.0/4096>max) max=event->Channels[channel].Data[j]*1.0/4096;
            test->Fill(j,event->Channels[channel].Data[j]*1.0/4096);
            test->GetYaxis()->SetRangeUser(min-((max-min)/20.0),max+((max-min)/20.0));
            test->SetLabelColor(kRed); 
            
            if( j<2 || j>1021 ) 
				Mean[j]=event->Channels[channel].Data[j]*1.0/4096;
			else 
				Mean[j]=0.2*(event->Channels[channel].Data[j+2]*1.0/4096+event->Channels[channel].Data[j+1]*1.0/4096+event->Channels[channel].Data[j]*1.0/4096+event->Channels[channel].Data[j-1]*1.0/4096+event->Channels[channel].Data[j-2]*1.0/4096);           
   			smooth->Fill(j,Mean[j]); 
            	
            //	std::cout << "Mean Value:" << Mean[k] << " " << "J-2 Value:" << j-2 << " " << std::endl;
            	smooth->GetYaxis()->SetRangeUser(min-((max-min)/20.0),max+((max-min)/20.0));
              	smooth->SetLabelColor(kGreen); 
			//	if(TMath::Abs(Mean-Sum_mean)/Sum_mean==)
			//	Sum_mean=[Sum*j+(event->Channels[channel].Data[j]*1.0/4096)]/(double)(j+1);
			
	  			Sum=Sum+Mean[j];
				if(Mean[j]>Max_mean) Max_mean=Mean[j];
				if(Mean[j]<Min_mean) Min_mean=Mean[j];				
		}	
/****************************Code for making a plot on Sig & Bkg @ SJTU Data***********************************************/		
		if(channel==10 || channel==13 ||channel==14 || channel==15)
		{
			for(int k=0;k<NbrTicks;++k) 
			{
				Sigma2=(Mean[k]-Sum/NbrTicks)*(Mean[k]-Sum/NbrTicks)+Sigma2;Sigma_y=sqrt(Sigma2/NbrTicks);
			}  //std::cout << "Mean[k]: " << Mean[k] << std::endl;}
		
			Bool_t Sig_true = false;
			for(Int_t a=0; a<Nsig; a++)
			{
				if(Signal_info[0][a]==i && Signal_info[1][a]==channel)	Sig_true = true; 	
			}
			if(Sig_true == true) 
			{
				Hist_SN_Ratio_sjtu->Fill((Sum/NbrTicks-Min_mean)/Sigma_y);
				Nsig_SJTU_Tot++; 		
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>4.000) Nsig_SJTUf++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>5.000) Nsig_SJTUw++;	
			}
			else 
			{
				Hist_BG_Ratio_sjtu->Fill((Sum/NbrTicks-Min_mean)/Sigma_y);
				Nbkg_Tot_s++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>4.000) Nbkg_sig_sf++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>5.000) Nbkg_sig_sw++;
			}		
		}
		std::cout << Nsig_SJTU_Tot << " \t" << "Successful!" <<std::endl;
/****************************Code for making a plot on Sig & Bkg @ USTC Data***********************************************/		
		if(channel==0 || channel==1 ||channel==2 || channel==3 || channel==4 || channel==5 || channel==6 || channel==7)	
		{
			for(int k=0;k<NbrTicks;++k) 
			{
				Sigma2=(Mean[k]-Sum/NbrTicks)*(Mean[k]-Sum/NbrTicks)+Sigma2;Sigma_y=sqrt(Sigma2/NbrTicks);
			}  //std::cout << "Mean[k]: " << Mean[k] << std::endl;}
		
			Bool_t Sig_true = false;
			for(Int_t a=0; a<Nsig; a++)
			{
				if(Signal_info[0][a]==i && Signal_info[1][a]==channel)	Sig_true = true; 	
			}
			if(Sig_true == true) 
			{
				Hist_SN_Ratio_ustc->Fill((Sum/NbrTicks-Min_mean)/Sigma_y); 
				Nsig_USTC_Tot++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>4.000) Nsig_USTCf++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>5.000) Nsig_USTCw++;
			}
			else 
			{
				Hist_BG_Ratio_ustc->Fill((Sum/NbrTicks-Min_mean)/Sigma_y);
				Nbkg_Tot_u++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>4.000) Nbkg_sig_uf++;
				if(((Sum/NbrTicks-Min_mean)/Sigma_y)>5.000) Nbkg_sig_uw++;	
			}
		}
		//std::cout << Nsig_USTC_Tot << " \t" << "Successful!" <<std::endl;
//		Hist_SigmaCh[channel]->Fill(Sigma_y);
//		Hist_SN_Ratio_ChN[channel]->Fill((Sum/NbrTicks-Min_mean)/Sigma_y);
//	 	Hist_SN_Ratio_ChP[channel]->Fill((Max_mean-Sum/NbrTicks)/Sigma_y);
 	
/****************************Code for finding a peak with signal/background***********************************************/
/*	 	NegSig_Truth[channel]=false; //Intialize the bool  
	 	if( (channel!=8 || channel!=17) && (Sum/NbrTicks-Min_mean)/Sigma_y>5)
	 	{
	 		log << "there is a negative signal!" 
		          << "\t" << "Sigma: "<< (Sum/NbrTicks-Min_mean)/Sigma_y << std::endl;
   			Nsig_neg_Ch[channel]++;
	   		NegSig_Truth[channel]=true; //if there is a signal at any channel
   			out << event->EventNumber << " " << Sigma_y << "\t" << "Negative!" <<"\n" ;
	 	}
	 	
	 	if((channel==8 || channel == 17) && (Sum/NbrTicks-Min_mean)/Sigma_y>2 )  //This is a trigger cut
	 	{
 			log << "there is a negative trigger signal!" 
		          << "\t" << "Sigma: "<< (Sum/NbrTicks-Min_mean)/Sigma_y << std::endl;
   			if(channel==8)Nsig_neg_Ch[8]++; else Nsig_neg_Ch[17]++;
   			out << event->EventNumber << " " << Sigma_y << "\t" << "Negative!" <<"\n" ;
 		} 
 */	
		can.Divide(1,2);
        can.cd(1);
		
	//	test->Smooth();
 		test->SetMarkerStyle(kFullSquare);
		test->SetTitle(("Event"+std::to_string(i)+"_Channel"+std::to_string(channel)).c_str());
 		test->Draw("HIST");
		
		can.cd(2);
		smooth->SetMarkerStyle(kFullSquare);
		smooth->SetTitle(("Smooth"+std::to_string(i)+"_Channel"+std::to_string(channel)).c_str());
 		smooth->Draw("HIST");
   	
   		
        //can.SaveAs(("Event&smooth"+std::to_string(i)+"_Channel"+std::to_string(channel)+".png").c_str());
        test->Clear();
		smooth->Clear(); 
  		}
/*	
	if(NegSig_Truth[0] || NegSig_Truth[1] || NegSig_Truth[2] || NegSig_Truth[3] || NegSig_Truth[4] || NegSig_Truth[5] || NegSig_Truth[6] || NegSig_Truth[7])
		Nsig_USTC++;
	
	if(NegSig_Truth[9] || NegSig_Truth[10] || NegSig_Truth[11] || NegSig_Truth[12] || NegSig_Truth[13] || NegSig_Truth[14] || NegSig_Truth[15] || NegSig_Truth[16])
		Nsig_SJTU++;		
  		
 	for(int ch=0;ch!=18;++ch)
 	{
		log << "Ch_" << ch << "\t" << "Num.signal(P&N): " << Nsig_pos_Ch[ch] << ", " << Nsig_neg_Ch[ch] << std::endl;	
	}	
	
	log << "*Nsig_USTC: " << Nsig_USTC << "Efficiency_USTC: " << Nsig_USTC/Nsig_neg_Ch[8] <<";\n" 
        << "*Nsig_SJTU: " << Nsig_SJTU << "Efficiency_SJTU: " << Nsig_SJTU/Nsig_neg_Ch[17]<< ";"  <<std::endl;
*///	log << "**********************************************************" << std::endl;
	
 //	if(i==nentries) Eff_file << Nsig_USTC/Nsig_neg_Ch[8] << " " << Nsig_SJTU/Nsig_neg_Ch[17] << std::endl;
   	}  //if end 
 
//	if((i%1000)==0)std::cout<< "Processed events:"<< i << ", \t" << (Float_t)i/nentries << std::endl;
     	event->clear();
		
   }  //Event end

/*******************************code for the process of output files*****************************/  

		ratiof << "\t" << "(Mean-MinValue)/RMS=Ratio>4" << "\t" << std::endl; 
		ratiof << "\t" << "Nsig" << "\t" << "Ntot(Efficiency%)" << "\t" << "Nbkg_Tot" << "\t" << "Err(Bkg->Sig)" <<std::endl;
		ratiof << "SJTU" << "\t" << Nsig_SJTUf << "\t" << Nsig_SJTU_Tot << "(" << 100.00*Nsig_SJTUf/Nsig_SJTU_Tot << "%)\t" << Nbkg_Tot_s << "\t" << 100.00*Nbkg_sig_sf/Nbkg_Tot_s << "%" << std::endl;   //SJTU-Ratio-4
		ratiof << "USTC" << "\t" << Nsig_USTCf << "\t" << Nsig_USTC_Tot << "(" << 100.00*Nsig_USTCf/Nsig_USTC_Tot << "%)\t" << Nbkg_Tot_u << "\t" << 100.00*Nbkg_sig_uf/Nbkg_Tot_u << "%" << std::endl;   //USTC-Ratio-4
		
		ratiow << "\t" << "(Mean-MinValue)/RMS=Ratio>5" << "\t" << std::endl; 
		ratiow << "\t" << "Nsig" << "\t" << "Ntot(Efficiency%)" << "\t" << "Nbkg_Tot" << "\t" << "Err(Bkg->Sig)" <<std::endl;
		ratiow << "SJTU" << "\t" << Nsig_SJTUw << "\t" << Nsig_SJTU_Tot << "(" << 100.00*Nsig_SJTUw/Nsig_SJTU_Tot << "%)\t" << Nbkg_Tot_s << "\t" << 100.00*Nbkg_sig_sw/Nbkg_Tot_s << "%" << std::endl;   //SJTU-Ratio-5
   	    ratiow << "USTC" << "\t" << Nsig_USTCw << "\t" << Nsig_USTC_Tot << "(" << 100.00*Nsig_USTCw/Nsig_USTC_Tot << "%)\t" << Nbkg_Tot_u << "\t" << 100.00*Nbkg_sig_uw/Nbkg_Tot_u << "%" << std::endl;   //USTC-Ratio-5
   
   out.close();
   log.close();
   ratiof.close();
   ratiow.close();
/*****************************code for USTC RPC Signal&Background******************************/ 
	c_SN_ustc->cd();
	TAxis *Xaxis_u = Hist_BG_Ratio_ustc->GetXaxis();	
	auto Yaxis_u = Hist_BG_Ratio_ustc->GetYaxis();	
	
	Xaxis_u->SetTitle("(Mean-MinValue)/RMS");
	Yaxis_u->SetTitle("Events/1");
	Xaxis_u->SetTitleSize(0.05);
	Yaxis_u->SetTitleSize(0.05);
	
	Hist_BG_Ratio_ustc->SetTitle("USCT RPC Signal&Background");
	Hist_BG_Ratio_ustc->SetFillColor(kBlue);
   	Hist_BG_Ratio_ustc->SetFillStyle(3008);
   	Hist_BG_Ratio_ustc->SetStats(0);	
   	Hist_BG_Ratio_ustc->Draw();
   
   	Hist_SN_Ratio_ustc->SetFillColor(kRed);
 	Hist_SN_Ratio_ustc->SetFillStyle(3003);
   	Hist_SN_Ratio_ustc->SetStats(0);
   	Hist_SN_Ratio_ustc->Draw("same");

   	TLegend *legend_u = new TLegend(.75,.80,.95,.95);
	legend_u->AddEntry(Hist_SN_Ratio_ustc, "Sig(Muon)");
	legend_u->AddEntry(Hist_BG_Ratio_ustc, "Bkg(Noise)");
	legend_u->Draw(); 
 	c_SN_ustc->SaveAs("../SN_ustc.pdf");
 	
/*****************************code for SJTU RPC Signal&Background******************************/
	c_SN_sjtu->cd();
	TAxis *Xaxis_s = Hist_BG_Ratio_sjtu->GetXaxis();
	auto Yaxis_s = Hist_BG_Ratio_sjtu->GetYaxis();

	Hist_BG_Ratio_sjtu->SetTitle("SJTU RPC Signal&Background");
	Hist_BG_Ratio_sjtu->SetFillColor(kBlue);
   	Hist_BG_Ratio_sjtu->SetFillStyle(3008);
   	Hist_BG_Ratio_sjtu->SetStats(0);
   	Hist_BG_Ratio_sjtu->Draw();
   
   	Hist_SN_Ratio_sjtu->SetFillColor(kRed);
   	Hist_SN_Ratio_sjtu->SetFillStyle(3003);
   	Hist_SN_Ratio_sjtu->SetStats(0);
   	Hist_SN_Ratio_sjtu->Draw("same");

	
	TLegend *legend_s = new TLegend(.75,.80,.95,.95);
	legend_s->AddEntry(Hist_SN_Ratio_sjtu, "Sig(Muon)");
	legend_s->AddEntry(Hist_BG_Ratio_sjtu, "Bkg(Noise)");
	legend_s->Draw();
   	c_SN_sjtu->SaveAs("../SN_sjtu.pdf");
   	
   	
 //  Eff_file.close();
   /*
   c_sigma->Divide(5,4);
  c_SNR->Divide(6,6);
   
   for(int ch=0; ch!=18; ch++)
   {
		c_sigma->cd(ch+1);
		Hist_SigmaCh[ch]->SetLineColor(kRed);
		Hist_SigmaCh[ch]->Draw("HIST");
   		Hist_SigmaCh[ch]->GetXaxis()->SetTitle("RMS_y");
   		Hist_SigmaCh[ch]->GetYaxis()->SetTitle("Events");
		Hist_SigmaCh[ch]->SetLineWidth(2);	
   		Hist_SigmaCh[ch]->SetTitle(("RMS_Ch"+std::to_string(ch)).c_str());
   	
   	 	c_SNR->cd(2*ch+1)->SetLogy();
		Hist_SN_Ratio_ChP[ch]->SetLineColor(kRed);
   		Hist_SN_Ratio_ChP[ch]->Draw("HIST");
   		Hist_SN_Ratio_ChP[ch]->GetXaxis()->SetTitle("(Maxpeak-mean)/RMS_y");
   		Hist_SN_Ratio_ChP[ch]->GetYaxis()->SetTitle("Events/0.17");
   		Hist_SN_Ratio_ChP[ch]->SetLineWidth(2);
   		Hist_SN_Ratio_ChP[ch]->GetXaxis()->SetTitleSize(0.05); 
   		Hist_SN_Ratio_ChP[ch]->GetYaxis()->SetTitleSize(0.05); 
   		Hist_SN_Ratio_ChP[ch]->SetTitle(("Hist_SN_Ratio_Ch"+std::to_string(ch)+"P").c_str());
  	
	  	c_SNR->cd(2*ch+2)->SetLogy();
		Hist_SN_Ratio_ChN[ch]->SetLineColor(kBlue);
   		Hist_SN_Ratio_ChN[ch]->Draw("HIST");
   		Hist_SN_Ratio_ChN[ch]->GetXaxis()->SetTitle("(mean-Minpeak)/RMS_y");
   		Hist_SN_Ratio_ChN[ch]->GetYaxis()->SetTitle("Events/0.17");
   		Hist_SN_Ratio_ChN[ch]->SetLineWidth(2);
   		Hist_SN_Ratio_ChN[ch]->GetXaxis()->SetTitleSize(0.05); 
   		Hist_SN_Ratio_ChN[ch]->GetYaxis()->SetTitleSize(0.05);
   		Hist_SN_Ratio_ChN[ch]->SetTitle(("Hist_SN_Ratio_Ch"+std::to_string(ch)+"N").c_str());
   		
	//	Eff[ch]=Nsig_neg_Ch[ch]/Nsig_neg_Ch[8];
   	//	std::cout << "Efficiency_" << ch << ": " << Eff[ch] << std::endl;
		   		
  
   }
  c_sigma->SaveAs("../Sigma_Dist.png");
	c_SNR->SaveAs("../SN_Ratio.png"); */ 
}   
