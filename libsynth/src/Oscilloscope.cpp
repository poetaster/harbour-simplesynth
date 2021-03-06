#include "../include/libsynth.hpp"
#include <future>

Oscilloscope::Oscilloscope::Buffer::Buffer(uint32_t sz, bool auto_thr)
: size(sz), auto_threshold(auto_thr)
{
	pos=0;
	buffer = new sgfloat [2*sz];
}

void Oscilloscope::Oscilloscope::Buffer::reset()
{
	pos = 0;
	lmax.value = -9e9;
	rmax.value = -9e9;
}

void Oscilloscope::Oscilloscope::Buffer::render(SDL_Renderer* r, int w, int h, bool draw_left, sgfloat  dx)
{
	int half = h/2;
	int coeff = (h-25)/2;
	SDL_SetRenderDrawColor(r, 128, 128, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(r, 0,half,w,half);
	SDL_RenderDrawLine(r, w/2, 0, w/2, h);
	SDL_SetRenderDrawColor(r, 0, 255, 0, SDL_ALPHA_OPAQUE);
	uint32_t p;
	if (draw_left)
		p=lmax.pos;
	else
		p=rmax.pos;

	sgfloat  x=0;

	int lastx=-1;
	int lasty=-1;

	while(p<pos && x<w)
	{
		int y = h - (half + buffer[p]*coeff);
		
		if (lastx==-1)
		{
			lastx = 0;
			lasty = y;
		}
		else
		{
			int xx=(int)x;
			if (xx > lastx)
			{
				SDL_RenderDrawLine(r, lastx, lasty, xx, y);
				lastx = xx;
				lasty = y;
			}
			x += dx;
		}
		p += 2;
	}
}

bool Oscilloscope::Buffer::fill(sgfloat  left, sgfloat  right)
{
	if (pos<size+1)
	{
		if (auto_threshold && pos>2)
		{
#if 0 // Synchro 1
			if (lmax.value < buffer[pos-2]-left)
			{
				lmax.value = buffer[pos-2]-left;
				lmax.pos = pos;
			}
#else // Synchro 2
			if (lmax.value<left && buffer[pos-2] < left)
			{
				lmax.value=left+0.02;
				lmax.pos=pos;
			}
			if (rmax.value<right && buffer[pos-1] < right)
			{
				rmax.value=right+0.02;
				rmax.pos=pos+1;
			}
#endif
		}
		buffer[pos++]=left;
		buffer[pos++]=right;
		return false;
	}
	return true;
}


Oscilloscope::Oscilloscope() : SoundGenerator("oscillo")
, buffer(0), sound(0)
{
}

Oscilloscope::~Oscilloscope()
{
	if (buffer)
		delete buffer;
	if (sound)
		delete sound;
}

Oscilloscope::Oscilloscope(istream& in)
{
	buffer = new Buffer(10000);
	sound = factory(in, true);
	if (SDL_Init(SDL_INIT_VIDEO))	// FIXME no a good place for that
	{
		cerr << "Unable to init video" << endl;
		exit(1);
	}
}

void Oscilloscope::next(sgfloat & left, sgfloat & right, sgfloat  speed)
{
	sgfloat  l=0;
	sgfloat  r=0;

	sound->next(l,r,speed);
	left += l;
	right += r;
	
	if (buffer->fill(l,r))
	{
		static atomic<bool> rendering(false);
		if (rendering)
			return;
		
		static SDL_Window* window = NULL;
		static SDL_Renderer* renderer = NULL;
		rendering = true;
		static Buffer* b = buffer;
		static thread* f = 0;
		if (f)
			f->join();
		f = new thread([]{
			if (window == NULL)
			{
				if (SDL_CreateWindowAndRenderer(640, 200, 0, &window, &renderer))
					return;
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			b->render(renderer, 640, 200, true, 1);
			SDL_RenderPresent(renderer);
			
			b->reset();
			rendering = false;
		});
		
		
	}
}
	
