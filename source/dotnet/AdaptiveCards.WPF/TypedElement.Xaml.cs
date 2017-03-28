using System.Threading.Tasks;

namespace Adaptive
{
    public partial class TypedElement 
    {
        public virtual Task PreRender()
        {
            return Task.Delay(0);
        }

        public virtual FrameworkElement Render(RenderContext context)
        {
            return new Grid();
        }

    }
}
